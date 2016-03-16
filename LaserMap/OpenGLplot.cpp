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
	glOrtho(xMin, xMax, yMin, yMax, gl_close, gl_far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Init variables
	openLASfile("C:/Users/Italo/Mis archivos/Universidad/1.-TfG/73.las");
}

void OpenGLplot::resizeGL(int w, int h)
{
	
// 	float dx = gl_width;
// 	float dy = gl_height;
// 
// 	dx *= (float)w / (float)h;
// 	dy *= (float)h / (float)w;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xMin, xMax, yMin, yMax, gl_close, gl_far);
	glMatrixMode(GL_MODELVIEW);

}

void OpenGLplot::paintEvent(QPaintEvent *e)
{
	//////////Paint points ////////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
// 	for (int i = 0; i < 1000; i++)
// 	{
// 		reader.ReadNextPoint();
// 		glVertex3d(p.GetX(), p.GetY(), -2.0);
// 		xMin = p.GetX() < (xMin) ? (p.GetX() - 1) : xMin;
// 		xMax = p.GetX() > (xMax) ? (p.GetX() + 1) : xMax;
// 		yMin = p.GetY() < (yMin) ? (p.GetY() - 1) : yMin;
// 		yMax = p.GetY() > (yMax) ? (p.GetY() + 1) : yMax;
// 		//gl_close = p.GetZ() < gl_close ? (p.GetZ() - 1) : gl_close;
// 		//gl_far = p.GetZ() > gl_far ? (p.GetZ() + 1) : gl_far;
// 		
// 	}
	glEnd();
	//qDebug() << "Datos de ortho " << xMin << ", " << xMax << "; " << yMin << ", " << yMax << "; " << gl_close << ", " << gl_far << "\n";
	//qDebug() << "resta " << p.GetX() - xMin << ", " << xMax - p.GetX() << "; " << p.GetY() - yMin << ", " << yMax - p.GetY() << "\n";
	//qDebug() << p.GetX() << ", " << p.GetY() << ", " << p.GetZ() << "\n";
}

void OpenGLplot::paintFileLAS(QString filename)
{
	int a = 5;
}

void OpenGLplot::openLASfile(QString filename)
{
	///////Open LAS file///////
	std::ifstream ifs;
	ifs.open(filename.toStdString(), std::ios::in | std::ios::binary);
	if (ifs.is_open())
		qDebug() << "\nabierto\n";
	liblas::ReaderFactory f;
	liblas::Reader reader = f.CreateWithStream(ifs);
	qDebug() << "\nintento pintar\n";

	for (int i = 0; i < 10; i++)
	{
		reader.ReadNextPoint();
		liblas::Point const &p = reader.GetPoint();
		liblas::Point newPoint(p);
		//pointList.append(newPoint);
		delete &newPoint;
	}
	
	qDebug() << "\ndejo de pintar\n";
}

