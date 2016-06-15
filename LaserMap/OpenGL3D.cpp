#include "OpenGL3D.h"


OpenGL3D::OpenGL3D(QWidget *parent, LaserPointList *laserPointListIn, QAction* actionColor)
{
	laserPointList = laserPointListIn;

	if (!actionColor->text().compare("HeightColor"))
		colorMode = HEIGHT_COLOR;
	else if (!actionColor->text().compare("ClassColor"))
		colorMode = CLASSIFICATION_COLOR;
	else if (!actionColor->text().compare("RealColor"))
		colorMode = REAL_COLOR;
	else
		colorMode = INTENSITY_COLOR;
}

OpenGL3D::OpenGL3D(QWidget *parent)
{

}


OpenGL3D::~OpenGL3D()
{
	//se llama al cerrar la ventana lasermap y cuando se crea un nuevo 3Dmap
}

/////////////////////////////////////////////////////
//////////////////OpenGL FUNCTIONS///////////////////
/////////////////////////////////////////////////////

void OpenGL3D::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	setFrustrumRange();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGL3D::resizeGL(int w, int h)
{
	//GLdouble ratioWidget = (GLdouble)w / (GLdouble)h;
	//updateGlOrtho(ratioWidget);
	glViewport(0, 0, w, h);
}

void OpenGL3D::paintGL()
{
	updateGlOrtho(width() / (GLdouble)height());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -frustumRange);
	glRotatef(xRotation, 1.0, 0.0, 0.0);
	glRotatef(yRotation, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	QList<LaserPoint> *pointList = laserPointList->getList();
	for (int i = 0; i < pointList->size(); i++)
	{
		LaserPoint p = pointList->at(i);
		setColor(p);
		glVertex3d(p.getX(), p.getY(), p.getZ());

	}
	glEnd();
}

void OpenGL3D::updateGlOrtho(GLdouble ratioWidget)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, ratioWidget, 0.0, frustumRange * 2);
	glMatrixMode(GL_MODELVIEW);
}

void OpenGL3D::setColor(LaserPoint point)
{
	GLdouble tempColor;
	GLdouble midRange;
	switch (colorMode)
	{
	case REAL_COLOR:
		glColor3f(point.getR(), point.getG(), point.getB());
		break;
	case INTENSITY_COLOR:
		tempColor = (point.getIntensity() - laserPointList->intensityMin) / (GLdouble)laserPointList->intensityLength;
		glColor3f(0.0, 1 - tempColor, tempColor);
		break;
	case CLASSIFICATION_COLOR:
		switch (point.getClassification())
		{
		case 0:
			//Not classified
			glColor3f(1.0, 1.0, 1.0);
			break;
		case 1:
			//Undefined
			glColor3f(1.0, 1.0, 1.0);
			break;
		case 2:
			//Ground
			glColor3f(0.549, 0.329, 0.094);
			break;
		case 3:
			//Low vegetation
			glColor3f(0.698, 0.917, 0.482);
			break;
		case 4:
			//Medium vegetation
			glColor3f(0.356, 0.819, 0.160);
			break;
		case 5:
			//High vegetation
			glColor3f(0.203, 0.541, 0.058);
			break;
		case 6:
			//Building
			glColor3f(0.823, 0.792, 0.117);
			break;
		case 7:
			//Low point (noise)
			glColor3f(0.780, 0.082, 0.058);
			break;
		case 8:
			//Model Key-point (mass point)
			glColor3f(0.780, 0.129, 0.909);
			break;
		case 9:
			//Water
			glColor3f(0.129, 0.372, 0.909);
			break;
		default:
			//Reserved
			glColor3f(0.129, 0.909, 0.874);
			break;
		}
		break;
	case HEIGHT_COLOR:
		midRange = laserPointList->zLength / 2;
		tempColor = point.getZ() - laserPointList->zMin;
		if (tempColor < midRange)
		{
			tempColor /= midRange;
			glColor3f(0.0f, tempColor, 1 - tempColor);
		}
		else
		{
			tempColor -= midRange;
			tempColor /= midRange;
			glColor3f(tempColor, 1 - tempColor, 0.0f);
		}
		break;
	}
}

void OpenGL3D::setFrustrumRange()
{
	frustumRange = abs(laserPointList->xMin);
	if (frustumRange < abs(laserPointList->xMax))
		frustumRange = abs(laserPointList->xMax);
	if (frustumRange < abs(laserPointList->yMin))
		frustumRange = abs(laserPointList->yMin);
	if (frustumRange < abs(laserPointList->yMax))
		frustumRange = abs(laserPointList->yMax);
	if (frustumRange < abs(laserPointList->zMin))
		frustumRange = abs(laserPointList->zMin);
	if (frustumRange < abs(laserPointList->zMax))
		frustumRange = abs(laserPointList->zMax);
	frustumRange += frustumRange / 6;
}

/////////////////////////////////////////////////////
/////////////////////MOUSE EVENTS////////////////////
/////////////////////////////////////////////////////

void OpenGL3D::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		initX = event->x();
		initY = event->y();
	}
}

void OpenGL3D::mouseMoveEvent(QMouseEvent *event)
{
	yRotation += ((event->x() - initX) * 360) / (GLdouble)width();
	xRotation += ((event->y() - initY) * 360) / (GLdouble)height();
	initX = event->x();
	initY = event->y();

	if (((int)xRotation % 360) == 0) xRotation = 0;
	if (((int)yRotation % 360) == 0) yRotation = 0;
	repaint();
}

void OpenGL3D::mouseReleaseEvent(QMouseEvent *event)
{

}

void OpenGL3D::wheelEvent(QWheelEvent *event)
{
	fovy -= (GLdouble)event->delta()/16.0;
	if (fovy < 10) fovy = 10;
	if (fovy > 180) fovy = 180;
	repaint();
}


/////////////////////////////////////////////////////
////////////////////////SLOTS////////////////////////
/////////////////////////////////////////////////////

void OpenGL3D::setClassColor()
{
	colorMode = CLASSIFICATION_COLOR;
	repaint();
}

void OpenGL3D::setHeightColor()
{
	colorMode = HEIGHT_COLOR;
	repaint();
}

void OpenGL3D::setRealColor()
{
	colorMode = REAL_COLOR;
	repaint();
}

void OpenGL3D::setIntensityColor()
{
	colorMode = INTENSITY_COLOR;
	repaint();
}