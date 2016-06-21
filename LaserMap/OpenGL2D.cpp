#include "OpenGL2D.h"

OpenGL2D::OpenGL2D(QWidget *parent)
	:QOpenGLWidget(parent)
{
}


OpenGL2D::OpenGL2D(QWidget *parent, LaserPointList *laserPointListIn)
	: QOpenGLWidget(parent)
{
	laserPointList = laserPointListIn;
	setMouseTracking(true);
	rubberBand = NULL;
	isLineDistance = false;
}

OpenGL2D::~OpenGL2D()
{
	if (rubberBand != NULL)
		delete rubberBand;
}

/////////////////////////////////////////////////////
//////////////////OpenGL FUNCTIONS///////////////////
/////////////////////////////////////////////////////

void OpenGL2D::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	//create and configure framebuffer
	glGenFramebuffers(1, &buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, buffer);
	glGenTextures(1, &renderedTexture);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenRenderbuffers(1, &renderedDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, renderedDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 2048, 1024);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderedDepth);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	updateFramebuffer = true;
	//reset matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGL2D::resizeGL(int w, int h)
{
	updateFramebuffer = true;
}

void OpenGL2D::paintGL()
{
	if (updateFramebuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, buffer);
		glViewport(0, 0, 2048, 1024);

		updateGlOrtho(width() / (GLdouble)height());
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
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		updateFramebuffer = false;
	}
	glViewport(0, 0, width(), height());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width(), 0.0, height(), 0.0, 3.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3i(0, 0, -2);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3i(width(), 0.0, -2);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3i(width(), height(), -2);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3i(0, height(), -2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	if (isLineDistance)
	{
		glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		//init
		glVertex3i(initX, height() - initY, -1);
		//end
		glVertex3i(endX, height() - endY, -1);
		glEnd();

	}
	glDisable(GL_TEXTURE_2D);
	glFlush();
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
		tempColor = (point.getIntensity() - laserPointList->intensityMin) / (GLdouble)laserPointList->intensityLength;
		glColor3f(0.0, 1-tempColor, tempColor);
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

void OpenGL2D::zoomGlOrtho(GLdouble *percent)
{
	laserPointList->yMin += laserPointList->yLength*(*percent) / 2;
	laserPointList->yMax -= laserPointList->yLength*(*percent) / 2;
	laserPointList->xMin += laserPointList->xLength*(*percent) / 2;
	laserPointList->xMax -= laserPointList->xLength*(*percent) / 2;
	laserPointList->yLength = laserPointList->yMax - laserPointList->yMin;
	laserPointList->xLength = laserPointList->xMax - laserPointList->xMin;
	laserPointList->percent *= (1 - (*percent));
	laserPointList->checkZoom();
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
			rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
			rubberBand->setGeometry(QRect(event->pos(), event->pos()).normalized());
			rubberBand->setVisible(true);
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
			rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
			rubberBand->setGeometry(QRect(event->pos(), event->pos()).normalized());
			rubberBand->setVisible(true);
		}
		break;
	case DISTANCE_MODE:
		if (event->button() == Qt::LeftButton)
		{
			initX = endX = event->x();
			initY = endY = event->y();
			isLineDistance = true;
		}
		break;
	default:
		break;
	}
}

void OpenGL2D::mouseMoveEvent(QMouseEvent *event)
{
	emit mouseMoved(translatePointX(event->x()), translatePointX(event->y()));
	switch (mouseMode)
	{
	case ZOOM_MODE:
		if ((event->buttons() & Qt::LeftButton) == Qt::LeftButton)
		{
			rubberBand->setGeometry(QRect(QPoint(initX,initY), event->pos()).normalized());
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
			updateFramebuffer = true;
			repaint();
		}
		break;
	case FIELD3D_MODE:
		if ((event->buttons() & Qt::LeftButton) == Qt::LeftButton)
		{
			rubberBand->setGeometry(QRect(QPoint(initX, initY), event->pos()).normalized());
		}
		break;
	case DISTANCE_MODE:
		if ((event->buttons() & Qt::LeftButton) == Qt::LeftButton)
		{
			endX = event->x();
			endY = event->y();
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
			rubberBand->setVisible(false);
			delete rubberBand;
			rubberBand = NULL;
			updateFramebuffer = true;
			repaint();
		}
		else if (event->button() == Qt::RightButton && mouseMode == ZOOM_MODE)
		{
			GLdouble percent = -0.5f;
			zoomGlOrtho(&percent);
			updateFramebuffer = true;
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
			updateFramebuffer = true;
			repaint();
		}
		break;
	case FIELD3D_MODE:
		if (event->button() == Qt::LeftButton)
		{
			LaserPoint init = LaserPoint(translatePointX(initX), translatePointY(initY));
			LaserPoint end = LaserPoint(translatePointX(event->x()), translatePointY(event->y()));
			rubberBand->setVisible(false);
			delete rubberBand;
			rubberBand = NULL;
			emit model3Dselected(init, end);
		}
		break;
	case DISTANCE_MODE:
		if (event->button() == Qt::LeftButton)
		{
			LaserPoint init = LaserPoint(translatePointX(initX), translatePointY(initY));
			LaserPoint end = LaserPoint(translatePointX(event->x()), translatePointY(event->y()));
			GLdouble distance = calculateDistance(init, end);
			QString message(" Distancia: ");
			message += QString::number(distance);
			isLineDistance = false;
			repaint();
			emit postMessage(message);
		}
		break;
	default:
		break;
	}
	emit mouseMoved(translatePointX(event->x()), translatePointX(event->y()));

}

/////////////////////////////////////////////////////
////////////////////////SLOTS////////////////////////
/////////////////////////////////////////////////////

void OpenGL2D::enableDrag()
{
	mouseMode = DRAG_MODE;
	emit postMessage("");
}

void OpenGL2D::enableZoom()
{
	mouseMode = ZOOM_MODE;
	emit postMessage("");
}

void OpenGL2D::enable3D()
{
	mouseMode = FIELD3D_MODE;
	emit postMessage("");
}

void OpenGL2D::enableDistance()
{
	mouseMode = DISTANCE_MODE;
	emit postMessage("");
}

void OpenGL2D::setClassColor()
{
	colorMode = CLASSIFICATION_COLOR;
	updateFramebuffer = true;
	repaint();
}

void OpenGL2D::setHeightColor()
{
	colorMode = HEIGHT_COLOR;
	updateFramebuffer = true;
	repaint();
}

void OpenGL2D::setRealColor()
{
	colorMode = REAL_COLOR;
	updateFramebuffer = true;
	repaint();
}

void OpenGL2D::setIntensityColor()
{
	colorMode = INTENSITY_COLOR;
	updateFramebuffer = true;
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

GLdouble OpenGL2D::calculateDistance(LaserPoint init, LaserPoint end)
{
	QList<LaserPoint>* pointList = laserPointList->getList();
	int listSize = pointList->size();
	GLdouble initZ = 0;
	for (int i = 0; i < listSize; i++)
	{
		LaserPoint p = pointList->at(i);
		if (abs(p.getX() - init.getX()) < 5 && abs(p.getY() - init.getY()) < 5)
		{
			initZ = p.getZ();
			break;
		}
	}
	GLdouble endZ = 0;
	for (int i = 0; i < listSize; i++)
	{
		LaserPoint p = pointList->at(i);
		if (abs(p.getX() - end.getX()) < 10 && abs(p.getY() - end.getY()) < 10)
		{
			endZ = p.getZ();
			break;
		}
	}
	return sqrt(pow((init.getX() - end.getX()), 2.0) + pow((init.getY() - end.getY()), 2.0) + pow(initZ - endZ, 2.0));
}
