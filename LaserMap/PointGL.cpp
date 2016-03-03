#include "PointGL.h"

PointGL::PointGL(QWidget *parent)
	:QOpenGLWidget(parent)
	, spin(0)
{
}


PointGL::~PointGL()
{
}

void PointGL::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0.0, 0.0, 0.0,0.0);
	glShadeModel(GL_FLAT);
}

void PointGL::paintEvent(QPaintEvent *e)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glRotatef(spin, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glRectf(-25.0, -25.0, 25.0, 25.0);

	/*
	spin = spin + 2.0;
	if (spin > 360.0)
		spin = spin - 360.0;
	*/
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(20.0, 20.0, 0.0);
	glVertex3f(25.0, 0.0, 0.0);
	glVertex3f(20.0, -20.0, 0.0);
	glVertex3f(-20.0, -20.0, 0.0);
	glVertex3f(-20.0, 20.0, 0.0);
	glEnd();
	/**/
}

void PointGL::resizeGL(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}