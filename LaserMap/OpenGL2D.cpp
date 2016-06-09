#include "OpenGL2D.h"

OpenGL2D::OpenGL2D(QWidget *parent)
	:QOpenGLWidget(parent)
{
}


OpenGL2D::OpenGL2D(QWidget *parent, LaserPointList *laserPointListIn)
	: QOpenGLWidget(parent)
{
	laserPointList = laserPointListIn;
}

OpenGL2D::~OpenGL2D()
{
}

/////////////////////////////////////////////////////
//////////////////OpenGL FUNCTIONS///////////////////
/////////////////////////////////////////////////////

void OpenGL2D::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGL2D::resizeGL(int w, int h)
{
	//GLdouble ratioWidget = (GLdouble)w / (GLdouble)h;
	//updateGlOrtho(ratioWidget);
	glViewport(0, 0, w, h);
}

void OpenGL2D::paintGL()
{
	updateGlOrtho(width()/(GLdouble)height());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	QList<LaserPoint> *pointList = laserPointList->getList();
	for (int i = 0; i < pointList->size(); i++)
	{
		LaserPoint p = pointList->at(i);
		setColor(p);
		glVertex3d(p.getX(), p.getY(), -(p.getZ()));

	}
	glEnd();
}

void OpenGL2D::setColor(LaserPoint point)
{
	GLdouble tempColor;
	GLdouble midRange;
	switch (colorMode)
	{
	case REAL_COLOR:
		glColor3f(point.getR(), point.getG(), point.getB());
		break;
	case INTENSITY_COLOR:
		glColor3f(point.getIntensity(), point.getIntensity(), point.getIntensity());
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
			glColor3f(1 - tempColor, tempColor, 0.0f);
		}
		break;
	}
}

void OpenGL2D::zoomGlOrtho(GLdouble *percent)
{
	laserPointList->yMin += laserPointList->yLength*(*percent) / 2;
	laserPointList->yMax -= laserPointList->yLength*(*percent) / 2;
	laserPointList->xMin += laserPointList->xLength*(*percent) / 2;
	laserPointList->xMax -= laserPointList->xLength*(*percent) / 2;
	laserPointList->yLength = laserPointList->yMax - laserPointList->yMin;
	laserPointList->xLength = laserPointList->xMax - laserPointList->xMin;
	laserPointList->percent *= (1 - (*percent));
}

void OpenGL2D::updateGlOrtho(GLdouble ratioWidget)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (laserPointList->getRatioMap() > ratioWidget)
	{
		glOrtho(laserPointList->xMin, laserPointList->xMax,
			laserPointList->yMin - (laserPointList->xLength * ((1 / ratioWidget) - (1 / laserPointList->getRatioMap()))) / 2.0, laserPointList->yMax + (laserPointList->xLength * ((1 / ratioWidget) - (1 / laserPointList->getRatioMap()))) / 2.0,
			laserPointList->zMin, laserPointList->zMax);

	}
	else
	{
		glOrtho(laserPointList->xMin - (laserPointList->yLength * (ratioWidget - laserPointList->getRatioMap())) / 2.0, laserPointList->xMax + (laserPointList->yLength * (ratioWidget - laserPointList->getRatioMap())) / 2.0,
			laserPointList->yMin, laserPointList->yMax,
			laserPointList->zMin, laserPointList->zMax);
	}
	glMatrixMode(GL_MODELVIEW);
}

void OpenGL2D::dragGlOrtho(GLdouble increment[])
{
	laserPointList->xMin += increment[0];
	laserPointList->xMax += increment[0];
	laserPointList->yMin += increment[1];
	laserPointList->yMax += increment[1];
	laserPointList->mapCenter[0] += increment[0];
	laserPointList->mapCenter[1] += increment[1];
}

/////////////////////////////////////////////////////
////////////////////////EVENTS///////////////////////
/////////////////////////////////////////////////////

void OpenGL2D::mousePressEvent(QMouseEvent *event)
{
	switch (mouseMode)
	{
	case ZOOM_MODE:
		if (event->button() == Qt::LeftButton)
		{
			initX = event->x();
			initY = event->y();
		}
		break;
	case DRAG_MODE:
		if (event->button() == Qt::LeftButton)
		{
			initX = event->x();
			initY = event->y();
		}
		break;
	case FIELD3D_MODE:
		if (event->button() == Qt::LeftButton)
		{
			initX = event->x();
			initY = event->y();
		}
		break;
	default:
		break;
	}
}

void OpenGL2D::mouseMoveEvent(QMouseEvent *event)
{
	switch (mouseMode)
	{
	case ZOOM_MODE:
		if ((event->buttons() & Qt::LeftButton) == Qt::LeftButton)
		{
			int a = 5;
			//pintar recuadro
			repaint();
		}
		break;
	case DRAG_MODE:
		if ((event->buttons() & Qt::LeftButton) == Qt::LeftButton)
		{
			//Moove from Init to actual Mouse coordinates
			GLdouble increment[2];
			increment[0] = translatePointX(initX) - translatePointX(event->x());
			increment[1] = translatePointY(initY) - translatePointY(event->y());
			dragGlOrtho(increment);
			//Update init
			initX = event->x();
			initY = event->y();
			qDebug() << "repintando...";
			resizeGL(width(), height());
			repaint();
		}
		break;
	case FIELD3D_MODE:
		if ((event->buttons() & Qt::LeftButton) == Qt::LeftButton)
		{
			int a = 5;
			//pintar recuadro
			repaint();
		}
		break;
	default:
		break;
	}
}

void OpenGL2D::mouseReleaseEvent(QMouseEvent *event)
{
	switch (mouseMode)
	{
	case ZOOM_MODE:
		if (event->button() == Qt::LeftButton)
		{
			GLdouble h = height();
			GLdouble w = width();
			//reducir el glortho
			GLdouble percent;
			GLdouble increment[2];
			GLdouble ratioWidget = w / h;
			//Calculate distance between Zoom Center and Map Center
			increment[0] = translatePointX(((initX + event->x()) / 2.0)) - laserPointList->mapCenter[0];
			increment[1] = translatePointY(((initY + event->y()) / 2.0)) - laserPointList->mapCenter[1];
			//Calculate zoom Percent
			if (laserPointList->getRatioMap() > ratioWidget) //rango X = rango ventana
				percent = 1 - abs(initX - event->x()) / w;
			else
				percent = 1 - abs(initY - event->y()) / h;
			//Adjust zoom and moove GlOrtho
			zoomGlOrtho(&percent);
			dragGlOrtho(increment);
			qDebug() << "repintando..";
			repaint();
		}
		else if (event->button() == Qt::RightButton && mouseMode == ZOOM_MODE)
		{
			laserPointList->resetData();
			repaint();
		}
		break;
	case DRAG_MODE:
		if (event->button() == Qt::LeftButton)
		{
			//Moove from Init to actual Mouse coordinates
			GLdouble increment[2];
			increment[0] = translatePointX(initX) - translatePointX(event->x());
			increment[1] = translatePointY(initY) - translatePointY(event->y());
			dragGlOrtho(increment);
			//Update init
			initX = event->x();
			initY = event->y();
			repaint();
		}
		break;
	case FIELD3D_MODE:
		if (event->button() == Qt::LeftButton)
		{
			LaserPoint init = LaserPoint(translatePointX(initX), translatePointY(initY));
			LaserPoint end = LaserPoint(translatePointX(event->x()), translatePointY(event->y()));
			emit model3Dselected(init, end);
		}
		break;
	default:
		break;
	}

}

/////////////////////////////////////////////////////
////////////////////////SLOTS////////////////////////
/////////////////////////////////////////////////////

void OpenGL2D::enableDrag()
{
	mouseMode = DRAG_MODE;
}

void OpenGL2D::enableZoom()
{
	mouseMode = ZOOM_MODE;
}

void OpenGL2D::enable3D()
{
	mouseMode = FIELD3D_MODE;
}

void OpenGL2D::enableDistance()
{
	mouseMode = DISTANCE_MODE;
}

void OpenGL2D::enableArea()
{
	mouseMode = AREA_MODE;
}

void OpenGL2D::setClassColor()
{
	colorMode = CLASSIFICATION_COLOR;
	repaint();
}

void OpenGL2D::setHeightColor()
{
	colorMode = HEIGHT_COLOR;
	repaint();
}

void OpenGL2D::setRealColor()
{
	colorMode = REAL_COLOR;
	repaint();
}

void OpenGL2D::setIntensityColor()
{
	colorMode = INTENSITY_COLOR;
	repaint();
}
/////////////////////////////////////////////////////
//////////////////PRIVATE FUNCTIONS//////////////////
/////////////////////////////////////////////////////

GLdouble OpenGL2D::translatePointX(GLdouble x)
{
	GLdouble point;
	GLdouble ratioWidget = width() / (GLdouble)height();
	if (laserPointList->getRatioMap() > ratioWidget) //rango X = rango ventana
	{
		point = laserPointList->xMin + laserPointList->xLength*(x / (GLdouble)width());
	}
	else
	{
		point = laserPointList->xMin - (laserPointList->yLength * (ratioWidget - laserPointList->getRatioMap())) / 2.0 +
			(laserPointList->xLength + (laserPointList->yLength * (ratioWidget - laserPointList->getRatioMap()))) * x / (GLdouble)width();
	}
	return point;
}

GLdouble OpenGL2D::translatePointY(GLdouble y)
{
	GLdouble point;
	GLdouble ratioWidget = width() / (GLdouble)height();
	if (laserPointList->getRatioMap() < ratioWidget) //rango X = rango ventana
	{
		point = laserPointList->yMin + laserPointList->yLength*(1 - y / (GLdouble)height());
	}
	else
	{
		point = laserPointList->yMin - (laserPointList->xLength * ((1 / ratioWidget) - (1 / laserPointList->getRatioMap()))) / 2.0 +
			(laserPointList->yLength + (laserPointList->xLength * ((1 / ratioWidget) - (1 / laserPointList->getRatioMap())))) * (1 - y / (GLdouble)height());
	}
	return point;
}