#include "OpenGL3D.h"


OpenGL3D::OpenGL3D(QWidget *parent, LaserPointList *laserPointListIn)
{

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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OpenGL3D::resizeGL(int w, int h)
{
	qDebug() << "reajustando";
	GLdouble ratioWidget = (GLdouble)w / (GLdouble)h;
	updateGlOrtho(ratioWidget);
	glViewport(0, 0, w, h);
}

void OpenGL3D::paintEvent(QPaintEvent *e)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	glVertex3d(0.0, 0.0, -1.0);
	glEnd();
}

void OpenGL3D::updateGlOrtho(GLdouble ratioWidget)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.0, 2.0);
}

/////////////////////////////////////////////////////
/////////////////////MOUSE EVENTS////////////////////
/////////////////////////////////////////////////////

void OpenGL3D::mousePressEvent(QMouseEvent *event)
{

}

void OpenGL3D::mouseMoveEvent(QMouseEvent *event)
{

}

void OpenGL3D::mouseReleaseEvent(QMouseEvent *event)
{

}

void OpenGL3D::closeEvent(QCloseEvent *event)
{
	qDebug() << "cerrando ventana 3D";
}

