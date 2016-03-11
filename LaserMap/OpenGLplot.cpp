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
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-gl_width / 2.0, gl_width / 2.0, -gl_height / 2.0, gl_height / 2.0, gl_close, gl_far);
}

void OpenGLplot::resizeGL(int w, int h)
{
	
// 	float dx = gl_width;
// 	float dy = gl_height;
// 
// 	dx *= (float)w / (float)h;
// 	dy *= (float)h / (float)w;
// 	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-gl_width / 2.0, gl_width / 2.0, -gl_height / 2.0, gl_height / 2.0, gl_close, gl_far);
}

void OpenGLplot::paintEvent(QPaintEvent *e)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	openLASfile();
}

void OpenGLplot::paintFileLAS(QString filename)
{
	int a = 5;
}

void OpenGLplot::openLASfile()
{
	std::ifstream ifs;
	ifs.open("C:/Users/Italo/Mis archivos/Universidad/1.-TfG/73.las", std::ios::in | std::ios::binary);
	if (ifs.is_open())
		qDebug() << "\nabierto\n";
	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);

// 	QList<liblas::Point> pointList = QList<liblas::Point>();
// 	for (int i = 0; i < 10; i++)
// 	{
// 		reader.ReadNextPoint();
// 		liblas::Point const &p = reader.GetPoint();
// 		pointList.insert(i,p);
// 		gl_width = abs(p.GetX()) >(gl_width / 2.0) ? (p.GetX()*2 + 5) : gl_width;
// 		gl_height = abs(p.GetY()) > (gl_height / 2.0) ? (p.GetY()*2 + 10) : gl_height;
// 		gl_close = -p.GetZ() > gl_close ? (p.GetZ() - 10) : gl_close;
// 		gl_far = -p.GetZ() < gl_far ? (p.GetZ() + 10) : gl_far;
// 		
// 	}
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	glVertex3d(1.0, 1.0, -2.0);
	for (int i = 0; i < 10; i++)
	{
		reader.ReadNextPoint();
		liblas::Point const &p = reader.GetPoint();
		glVertex3d(p.GetX()/3, p.GetY()/3, -2.0);
		glVertex3d(1.15233 * 1000000, 1.09266 * 1000000, -2.0);
		gl_width = abs(p.GetX()) >(gl_width / 2.0) ? (p.GetX() * 2 + p.GetX()/2) : gl_width;
		gl_height = abs(p.GetY()) > (gl_height / 2.0) ? (p.GetY() * 2 + p.GetY()/2) : gl_height;
		//gl_close = -p.GetZ() > gl_close ? (p.GetZ() - 10) : gl_close;
		//gl_far = -p.GetZ() < gl_far ? (p.GetZ() + 10) : gl_far;
		qDebug() << p.GetX() << ", " << p.GetY() << ", " << p.GetZ() << "\n";
	}
	glEnd();
	glFlush();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-gl_width / 2.0, gl_width / 2.0, -gl_height / 2.0, gl_height / 2.0, gl_close, gl_far);
	qDebug() <<"Datos de ortho "<< gl_width/2 << ", " << gl_height/2 << ", " << gl_close << ", " << gl_far << "\n";

}
