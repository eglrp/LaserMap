#ifndef OPENGLPLOT_H
#define OPENGLPLOT_H
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qopenglwidget.h>
#include <QtOpenGL>
#include <qopenglcontext.h>
#include <gl\GLU.h>
#include <liblas/liblas.hpp>
#include <fstream>  // std::ifstream
#include <iostream>
#include <QDebug>


class OpenGLplot : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	OpenGLplot(QWidget *parent);
	~OpenGLplot();	

protected:
	virtual void initializeGL();
	virtual void paintEvent(QPaintEvent *e);
	virtual void resizeGL(int w, int h);

public slots:
	void paintFileLAS(QString filename);

private:
	GLdouble xMin = 1.0, xMax = 1.0, yMin = 1.0, yMax = 1.0, gl_close = 1.0, gl_far = 1.0;
	QList<liblas::Point> pointList;
	//liblas::Header header;
	void openLASfile(QString filename);
};



#endif
