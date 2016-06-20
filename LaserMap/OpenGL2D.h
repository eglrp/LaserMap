#ifndef OPENGL2D_H
#define OPENGL2D_H
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qopenglwidget.h>
#include <QtOpenGL>
#include <QList>
#include <math.h>
#include "laserpoint.h"
#include "OpenGL3D.h"
#include "LaserPointList.h"
#define DRAG_MODE 0
#define ZOOM_MODE 1
#define DISTANCE_MODE 2
#define FIELD3D_MODE 3

#define REAL_COLOR 0
#define INTENSITY_COLOR 1
#define CLASSIFICATION_COLOR 2
#define HEIGHT_COLOR 3

class OpenGL2D : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	OpenGL2D(QWidget *parent, LaserPointList *laserPointListIn);
	OpenGL2D(QWidget *parent);
	~OpenGL2D();

signals:
	void model3Dselected(LaserPoint init, LaserPoint end);
	void mouseMoved(int x, int y);
	void postMessage(QString message);

public slots:
	void enableDrag();
	void enableZoom();
	void enableDistance();
	void enable3D();
	void setHeightColor();
	void setClassColor();
	void setIntensityColor();
	void setRealColor();

private:
	LaserPointList *laserPointList;
	int initX, initY;
	int mouseMode = ZOOM_MODE;
	int colorMode = HEIGHT_COLOR;
	//Private functions
	void updateGlOrtho(GLdouble ratioWidget);
	void setColor(LaserPoint point);
	void zoomGlOrtho(GLdouble *percent);
	void dragGlOrtho(GLdouble increment[]);
	GLdouble translatePointX(GLdouble x);
	GLdouble translatePointY(GLdouble y);
	//QOpenGLFunctions inherited
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);
	//QWidget events inherited
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	GLdouble calculateDistance(LaserPoint init, LaserPoint end);
};



#endif
