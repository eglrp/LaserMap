#ifndef OPENGL3D_H
#define OPENGL3D_H
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qopenglwidget.h>
#include <QtOpenGL>
#include <GL/GLU.h>
#include <QList>
#include "laserpoint.h"
#include "LaserPointList.h"

#define REAL_COLOR 0
#define INTENSITY_COLOR 1
#define CLASSIFICATION_COLOR 2
#define HEIGHT_COLOR 3

class OpenGL3D : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	OpenGL3D(QWidget *parent, LaserPointList *laserPointListIn, QAction* actionColor);
	OpenGL3D(QWidget *parent);
	~OpenGL3D();

public slots:
	void setHeightColor();
	void setClassColor();
	void setIntensityColor();
	void setRealColor();

private:
	GLdouble xRotation = 315;
	GLdouble yRotation = 0;
	GLdouble fovy = 90.0;
	GLdouble frustumRange;
	LaserPointList *laserPointList;
	int colorMode;
	int initX, initY;
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);

	void setColor(LaserPoint point);
	void setFrustrumRange();
	void updateGlOrtho(GLdouble ratioWidget);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
};

#endif
