#ifndef OPENGLPLOT_H
#define OPENGLPLOT_H
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qopenglwidget.h>
#include <QtOpenGL>
#include <QList>
#include <QDebug>
#include "laserpoint.h"
#include "LaserPointList.h"
#define DRAG_MODE 0
#define ZOOM_MODE 1
#define DISTANCE_MODE 2
#define AREA_MODE 3

class OpenGLplot : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	OpenGLplot::OpenGLplot(QWidget *parent, LaserPointList *laserPointListIn);
	OpenGLplot(QWidget *parent);
	~OpenGLplot();

public slots:
	void enableDrag();
	void enableZoom();
	void setHeightColor();
	void setClassColor();

protected:
	virtual void initializeGL();
	virtual void paintEvent(QPaintEvent *e);
	virtual void resizeGL(int w, int h);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:
	LaserPointList *laserPointList;
	QList<LaserPoint*> pointList;
	int initX, initY;
	int mouseMode = ZOOM_MODE;
	void updateGlOrtho(GLdouble ratioWidget);
	void setColor(GLshort classification);
	void zoomGlortho(GLdouble *percent);
	void mooveGlortho(GLdouble mooveCenter[]);
	GLdouble translatePointX(int x);
	GLdouble translatePointY(int y);
};



#endif
