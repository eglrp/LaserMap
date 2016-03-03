#include "PointGL.h"

PointGL::PointGL(QWidget *parent)
	:QOpenGLWidget(parent)
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
	glEnable(GL_DEPTH_TEST);
}

void PointGL::paintEvent(QPaintEvent *e)
{
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(20.0, 20.0, 0.0);
	glVertex3f(25.0, 0.0, 0.0);
	glVertex3f(20.0, -20.0, 0.0);
	glVertex3f(-20.0, -20.0, 0.0);
	glVertex3f(-20.0, 20.0, 0.0);
	glEnd();
	*/

	drawCube();
	/**/
}

void PointGL::resizeGL(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -5.0, 5.0); //define el espacio que se puede visualizar enfrente de la camara
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void PointGL::drawCube(void)
{
	glColor3f(1.0f, 0.0f, 0.0f);//rojo
	glBegin(GL_QUADS);       //cara frontal
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);//verde

	glBegin(GL_QUADS);       //cara trasera
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);       //cara lateral izq
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);       //cara lateral dcha
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);       //cara arriba
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);       //cara abajo
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();
}