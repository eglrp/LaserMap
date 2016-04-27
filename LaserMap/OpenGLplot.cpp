#include "OpenGLplot.h"

OpenGLplot::OpenGLplot(QWidget *parent)
	:QOpenGLWidget(parent)
{
}


OpenGLplot::OpenGLplot(QWidget *parent, LaserPointList *laserPointListIn)
	:QOpenGLWidget(parent)
{
	laserPointList = laserPointListIn;
}

OpenGLplot::~OpenGLplot()
{
	qDeleteAll(pointList);
}

/////////////////////////////////////////////////////
//////////////////OpenGL FUNCTIONS///////////////////
/////////////////////////////////////////////////////

void OpenGLplot::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0.0, 0.0, 0.0,0.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGLplot::resizeGL(int w, int h)
{
	qDebug() << "reajustando";
	GLdouble ratioWidget = (GLdouble)w / (GLdouble)h;
	updateGlOrtho(ratioWidget);
	glViewport(0, 0, w, h);
}

void OpenGLplot::paintEvent(QPaintEvent *e)
{
	qDebug() << "repintando";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	QList<LaserPoint> *pointList = laserPointList->getList();
	for (int i = 0; i < pointList->size(); i++)
	{
		LaserPoint p = pointList->at(i);
		//setColor(p.GetClassification());
		GLfloat normalizeZ = (p.getZ() - laserPointList->zMin) / (laserPointList->zMax - laserPointList->zMin);
		glColor3f(normalizeZ, normalizeZ, normalizeZ);
		glVertex3d(p.getX(), p.getY(), -(p.getZ()));

	}
	glEnd();
}

void OpenGLplot::setColor(GLshort classification)
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
	glColor3f(1.0, 1.0, 1.0);
}

void OpenGLplot::zoomGlOrtho(GLdouble *percent)
{
	laserPointList->yMin += laserPointList->yLength*(*percent) / 2;
	laserPointList->yMax -= laserPointList->yLength*(*percent) / 2;
	laserPointList->xMin += laserPointList->xLength*(*percent) / 2;
	laserPointList->xMax -= laserPointList->xLength*(*percent) / 2;
	laserPointList->yLength = laserPointList->yMax - laserPointList->yMin;
	laserPointList->xLength = laserPointList->xMax - laserPointList->xMin;
	laserPointList->percent *= (1 - (*percent));
}

void OpenGLplot::updateGlOrtho(GLdouble ratioWidget)
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

void OpenGLplot::dragGlOrtho(GLdouble increment[])
{
	laserPointList->xMin += increment[0];
	laserPointList->xMax += increment[0];
	laserPointList->yMin += increment[1];
	laserPointList->yMax += increment[1];
	laserPointList->mapCenter[0] += increment[0];
	laserPointList->mapCenter[1] += increment[1];
}

/////////////////////////////////////////////////////
/////////////////////MOUSE EVENTS////////////////////
/////////////////////////////////////////////////////

void OpenGLplot::mousePressEvent(QMouseEvent *event)
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
	default:
		break;
	}
}

void OpenGLplot::mouseMoveEvent(QMouseEvent *event)
{
	switch (mouseMode)
	{
	case ZOOM_MODE:
		if (event->button() == Qt::LeftButton)
		{
			int a = 5;
			//pintar recuadro
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
		}
		break;
	default:
		break;
	}
}

void OpenGLplot::mouseReleaseEvent(QMouseEvent *event)
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
			updateGlOrtho(ratioWidget);
		}
		else if (event->button() == Qt::RightButton && mouseMode == ZOOM_MODE)
		{
			laserPointList->resetData();
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
		}
		break;
	default:
		break;
	}
	
}

GLdouble OpenGLplot::translatePointX(GLdouble x)
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

GLdouble OpenGLplot::translatePointY(GLdouble y)
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

/////////////////////////////////////////////////////
////////////////////////SLOTS////////////////////////
/////////////////////////////////////////////////////

void OpenGLplot::enableDrag()
{
	mouseMode = DRAG_MODE;
}

void OpenGLplot::enableZoom()
{
	mouseMode = ZOOM_MODE;
}

void OpenGLplot::setClassColor()
{
	int a = 5;
}

void OpenGLplot::setHeightColor()
{
	int a = 5;
}
