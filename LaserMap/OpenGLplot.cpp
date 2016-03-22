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
		qDebug() << "\nabierto\n";
	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);
	liblas::Header const &header = reader.GetHeader();
	numPuntos = header.GetPointRecordsCount();
	xMin = header.GetMinX();
	xMax = header.GetMaxX();
	yMin = header.GetMinY();
	yMax = header.GetMaxY();
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
	GLfloat dx, dy = 1.0;
	if (w > h){
		dx = (GLfloat)w / (GLfloat)h;
	}
	if (h > w){
		dy = (GLfloat)h / (GLfloat)w;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xMin, xMax, yMin, yMax, zMin, zMax);
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
		qDebug() << "\nabierto\n";
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
		setColor(p.GetClassification());
		//GLfloat normalizeZ = (p.GetZ() - zMin) / (zMax - zMin);
		//glColor3f(normalizeZ, normalizeZ, normalizeZ);
		glVertex3d(p.GetX(), p.GetY(), -p.GetZ());
	}
	glEnd();
}

void OpenGLplot::paintFileLAS(QString filename)
{
	int a = 5;
}

void OpenGLplot::setColor(liblas::Classification const &pointClass)
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
	glColor3f(1.0, 1.0, 1.0);
}
