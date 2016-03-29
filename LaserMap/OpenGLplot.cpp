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
	xMinInit = xMin = header.GetMinX();
	xMaxInit = xMax = header.GetMaxX();
	xLengthInit = xLength = xMax - xMin;
	yMinInit = yMin = header.GetMinY();
	yMaxInit = yMax = header.GetMaxY();
	yLengthInit = yLength = yMax - yMin;
	zMin = header.GetMinZ();
	zMax = header.GetMaxZ();
	ratioMap = xLength / yLength;
	mapCenter[0] = xMin + xLength / 2;
	mapCenter[1] = yMin + yLength / 2;

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
	if (ratioMap > ratioWidget)
	{
		glOrtho(xMin, xMax,
			yMin - (xLength * ((1 / ratioWidget) - (1 / ratioMap))) / 2, yMax + (xLength * ((1 / ratioWidget) - (1 / ratioMap))) / 2,
			zMin, zMax);
		 
	}
	else
	{
		glOrtho(xMin - (xLength * (ratioWidget - ratioMap)) / 2, xMax + (xLength * (ratioWidget - ratioMap)) / 2,
			yMin, yMax,
			zMin, zMax);
	}
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void OpenGLplot::paintEvent(QPaintEvent *e)
{
	///////Open LAS file///////
	std::ifstream ifs;
	ifs.open("C:/Users/Italo/Mis archivos/Universidad/1.-TfG/73.las", std::ios::in | std::ios::binary);
	if (ifs.is_open())
		qDebug() << "repintando";
	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);

	glClear(GL_COLOR_BUFFER_BIT);
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
		initX = event->x();
		initY = event->y();
	}
}

void OpenGLplot::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		int h = height();
		int w = width();
		//reducir el glortho
		GLdouble percent;
		if (ratioMap > ((GLdouble)w / (GLdouble)h)) //rango X = rango ventana
		{
			percent = 1 - abs(initX - event->x()) / (GLdouble)w;
		}
		else
		{
			percent = 1 - abs(initY - event->y()) / (GLdouble)h;
		}
		GLdouble zoomCenter[2] = {
			xMin + xLength*(((initX + event->x()) / 2) / (GLdouble)w),
			yMin + yLength*(((initY + event->y()) / 2) / (GLdouble)h),
		};
		qDebug() << "mapCenter: " << mapCenter[0] << ", " << mapCenter[1] <<
			"; ZoomCenter: " << mapCenter[0] << ", " << zoomCenter[1];

		//reducir glortho
		yMin = yMin + yLength*percent / 2;
		yMax = yMax - yLength*percent / 2;
		xMin = xMin + xLength*percent / 2;
		xMax = xMax - xLength*percent / 2;
		//centrar glortho con el centro del recuadro
// 		GLdouble diference = zoomCenter[0] - mapCenter[0];
// 		xMin = xMin + diference;
// 		xMax = xMax + diference;
// 		diference = zoomCenter[1] - mapCenter[1];
// 		yMin = yMin + diference;
// 		yMax = yMax + diference;

		mapCenter[0] = zoomCenter[0];
		mapCenter[1] = zoomCenter[1];
		yLength = yMax - yMin;
		xLength = xMax - xMin;

		//relanzar resizeGL? o glortho
	}
	else if (event->button() == Qt::RightButton)
	{
		xMin = xMinInit;
		xMax = xMaxInit;
		xLength = xLengthInit;
		yMin = yMinInit;
		yMax = yMaxInit;
		yLength = yLengthInit;
		mapCenter[0] = xMin + xLength / 2;
		mapCenter[1] = yMin + yLength / 2;
	}
}

