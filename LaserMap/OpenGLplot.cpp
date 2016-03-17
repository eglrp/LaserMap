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
	initializeOpenGLFunctions();
	glClearColor(0.0, 0.0, 0.0,0.0);
	//glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGLplot::resizeGL(int w, int h)
{
	
// 	float dx = gl_width;
// 	float dy = gl_height;
// 
// 	dx *= (float)w / (float)h;
// 	dy *= (float)h / (float)w;
	//glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-xMax, xMax, -yMax, yMax, -zMax, zMax);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
// 	gluLookAt((xMin + xMax) / 2, (yMin + yMax) / 2, zMin,
// 		(xMin + xMax) / 2, (yMin + yMax) / 2, (zMin + zMax) / 2,
// 		(xMin + xMax) / 2, yMax, zMin);

}

void OpenGLplot::paintEvent(QPaintEvent *e)
{
	///////Open LAS file///////
	std::ifstream ifs;
	ifs.open("C:/Users/Italo/Mis archivos/Universidad/1.-TfG/73.las", std::ios::in | std::ios::binary);
	if (ifs.is_open())
		qDebug() << "\nabierto\n";
	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);
	liblas::Header const &header = reader.GetHeader();
	xMin = header.GetMinX();
	xMax = header.GetMaxX();
	yMin = header.GetMinY();
	yMax = header.GetMaxY();
	zMin = header.GetMinZ();
	zMax = header.GetMaxZ();

	//////////Paint points////////
	glLoadIdentity();
	//glTranslatef(-((xMax + xMin) / 2), -((yMax + yMin) / 2), 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < header.GetPointRecordsCount(); i++)
	{
		reader.ReadNextPoint();
		liblas::Point const &p = reader.GetPoint();
		glVertex3d(p.GetX(), p.GetY(), p.GetZ());
	}
	glEnd();

	qDebug() << "numero de puntos: " << header.GetPointRecordsCount() << "\n";
	qDebug() << "Datos de ortho: " << xMin << ", " << xMax << "; " << yMin << ", " << yMax << "; " << zMin << ", " << zMax << "\n";
	qDebug() << "Datos de lookAt: " << (xMin + xMax) / 2 << ", " << (yMin + yMax) / 2 << ", " << zMin << "; " << (xMin + xMax) / 2 << ", " << (yMin + yMax) / 2 << ", " << (zMin + zMax) / 2 << "; " << (xMin + xMax) / 2 << ", " << yMax << ", " << zMin << "\n";
	//qDebug() << "Datos de translatef: " << -((xMin + xMax) / 2) << ", " << -((yMin + yMax) / 2) << ", " << -((zMin + zMax) / 2) - 2.0 << "\n";
	//qDebug() << "Resta " << p.GetX() - xMin << ", " << xMax - p.GetX() << "; " << p.GetY() - yMin << ", " << yMax - p.GetY() << "\n";
	liblas::Point const &p = reader.GetPoint();
	qDebug() << p.GetX() << ", " << p.GetY() << ", " << p.GetZ() << "\n";
}

void OpenGLplot::paintFileLAS(QString filename)
{
	int a = 5;
}