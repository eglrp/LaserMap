#ifndef OPENGL3D_H
#define OPENGL3D_H
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qopenglwidget.h>
#include <QtOpenGL>
#include <QList>
#include <QDebug>
#include "laserpoint.h"
#include "LaserPointList.h"

class OpenGL3D : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	OpenGL3D(QWidget *parent, LaserPointList *laserPointListIn);
	OpenGL3D(QWidget *parent);
	~OpenGL3D();

private:
	void updateGlOrtho(GLdouble ratioWidget);
	LaserPointList *laserPointList;
	int initX, initY;
	void initializeGL();
	void paintEvent(QPaintEvent *e);
	void resizeGL(int w, int h);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void closeEvent(QCloseEvent *event);
};

#endif
