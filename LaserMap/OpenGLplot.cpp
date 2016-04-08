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
	glViewport(0, 0, w, h);
}

void OpenGLplot::paintEvent(QPaintEvent *e)
{
	qDebug() << "repintando";
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
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

void OpenGLplot::mousePressEvent(QMouseEvent *event)
{
	switch (mouseMode)
	{
	case ZOOM_MODE:
		if (event->button() == Qt::LeftButton && mouseMode == ZOOM_MODE)
		{
			initX = event->x();
			initY = event->y();
		}
		break;
	case DRAG_MODE:
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
			int h = height();
			int w = width();
			//reducir el glortho
			GLdouble percent;
			GLdouble zoomCenter[2];
			GLdouble ratioWidget = (GLdouble)w / (GLdouble)h;
			if (laserPointList->getRatioMap() > ratioWidget) //rango X = rango ventana
			{
				percent = 1 - abs(initX - event->x()) / (GLdouble)w;

				zoomCenter[0] = laserPointList->xMin + laserPointList->xLength*(((initX + event->x()) / 2.0) / (GLdouble)w);
				zoomCenter[1] = laserPointList->yMin - (laserPointList->xLength * ((1 / ratioWidget) - (1 / laserPointList->getRatioMap()))) / 2.0 + (laserPointList->yLength + (laserPointList->xLength * ((1 / ratioWidget) - (1 / laserPointList->getRatioMap())))) * (1 - ((initY + event->y()) / 2.0) / (GLdouble)h);
			}
			else
			{
				percent = 1 - abs(initY - event->y()) / (GLdouble)h;

				zoomCenter[1] = laserPointList->yMin + laserPointList->yLength*(1 - ((initY + event->y()) / 2.0) / (GLdouble)h);
				zoomCenter[0] = laserPointList->xMin - (laserPointList->yLength * (ratioWidget - laserPointList->getRatioMap())) / 2.0 + (laserPointList->xLength + (laserPointList->yLength * (ratioWidget - laserPointList->getRatioMap()))) * ((initX + event->x()) / 2.0) / (GLdouble)w;
			}
			zoomGlortho(zoomCenter, &percent);
		}
		else if (event->button() == Qt::RightButton && mouseMode == ZOOM_MODE)
		{
			laserPointList->resetData();
		}
		break;
	case DRAG_MODE:
		break;
	default:
		break;
	}
	
}

void OpenGLplot::zoomGlortho(GLdouble zoomCenter[], GLdouble *percent)
{
	//reducir glortho
	laserPointList->yMin += laserPointList->yLength*(*percent) / 2;
	laserPointList->yMax -= laserPointList->yLength*(*percent) / 2;
	laserPointList->xMin += laserPointList->xLength*(*percent) / 2;
	laserPointList->xMax -= laserPointList->xLength*(*percent) / 2;

	//centrar glortho con el centro del recuadro
	GLdouble diference = zoomCenter[0] - laserPointList->mapCenter[0];
	laserPointList->xMin += diference;
	laserPointList->xMax += diference;
	diference = zoomCenter[1] - laserPointList->mapCenter[1];
	laserPointList->yMin += diference;
	laserPointList->yMax += diference;
	laserPointList->mapCenter[0] = zoomCenter[0];
	laserPointList->mapCenter[1] = zoomCenter[1];
	laserPointList->yLength = laserPointList->yMax - laserPointList->yMin;
	laserPointList->xLength = laserPointList->xMax - laserPointList->xMin;
	//relanzar resizeGL? o glortho
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

