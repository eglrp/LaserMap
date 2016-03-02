#ifndef POINTGL_H
#define POINTGL_H
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qopenglwidget.h>
#include <QtOpenGL>
#include <qopenglcontext.h>


class PointGL : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	PointGL(QWidget *parent);
	~PointGL();	

protected:
	virtual void initializeGL();
	virtual void paintEvent(QPaintEvent *e);
	virtual void resizeGL(int w, int h);

private:
	float spin;

};



#endif
