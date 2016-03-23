#include "OpenGLplot.h"

OpenGLplot::OpenGLplot(QWidget *parent)
	:QOpenGLWidget(parent)
{
}

OpenGLplot::~OpenGLplot()
{
}

void OpenGLplot::initializeGL()
{
	std::ifstream ifs;
	ifs.open("C:/Users/Italo/Mis archivos/Universidad/1.-TfG/73.las", std::ios::in | std::ios::binary);
	if (ifs.is_open())
		qDebug() << "inicializado";
	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);
	liblas::Header const &header = reader.GetHeader();
	numPuntos = header.GetPointRecordsCount();
	xMin = header.GetMinX();
	xMax = header.GetMaxX();
	xLength = xMax - xMin;
	yMin = header.GetMinY();
	yMax = header.GetMaxY();
	yLength = yMax - yMin;
	zMin = header.GetMinZ();
	zMax = header.GetMaxZ();

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
	GLdouble ratioRelation = (GLdouble)w / (GLdouble)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (xLength / yLength > ratioRelation)
	{
		glOrtho(xMin, xMax,
			yMin - yLength*ratioRelation, yMax + yLength*ratioRelation,
			zMin, zMax);
		 
	}
	else
	{
		glOrtho(xMin - xLength *ratioRelation, xMax + xLength *ratioRelation,
			yMin, yMax,
			zMin, zMax);
	}
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void OpenGLplot::paintEvent(QPaintEvent *e)
{
	///////Open LAS file///////
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);

	std::ifstream ifs;
	ifs.open("C:/Users/Italo/Mis archivos/Universidad/1.-TfG/73.las", std::ios::in | std::ios::binary);
	if (ifs.is_open())
		qDebug() << "repintando";
	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < numPuntos; i++)
	{
		reader.ReadNextPoint();
		liblas::Point const &p = reader.GetPoint();
		//setColor(p.GetClassification());
		GLfloat normalizeZ = (p.GetZ() - zMin) / (zMax - zMin);
		glColor3f(normalizeZ, normalizeZ, normalizeZ);
		glVertex3d(p.GetX(), p.GetY(), -p.GetZ());
	}
	glEnd();
}

void OpenGLplot::setColor(liblas::Classification const &pointClass)
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
	glColor3f(1.0, 1.0, 1.0);
}

void OpenGLplot::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		qDebug() << "El raton se encuentra en: " << event->x() << ", " << event->y();
		initX = event->x();
		initY = event->y();
	}
}

void OpenGLplot::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		//Hay que calcular los valores equivalentes en OpenGL
// 		if (initX > event->x())
// 		{
// 			xMin = (event->x()/width())*xLength + xMin;
// 			xMax = (initX / width())*xLength + xMin;
// 		}
// 		else
// 		{
// 			xMin = (initX / width())*xLength + xMin;
// 			xMax = (event->x() / width())*xLength + xMin;
// 		}
// 		xLength = xMax - xMin;
// 
// 		if (initY > event->y())
// 		{
// 			yMin = (event->y()/width())*yLength + xMin;
// 			yMax = (initY / height())*yLength + xMin;
// 		}
// 		else
// 		{
// 			yMin = (event->y() / width())*yLength + xMin;
// 			yMax = (initY / height())*yLength + xMin;
// 		}
// 		yLength = yMax - yMin;
		qDebug() << "El raton se libera en: " << event->x() << ", " << event->y();
	}
}
