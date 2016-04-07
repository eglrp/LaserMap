#include "lasermap.h"

LaserMap::LaserMap(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//File loader connections
 	connect(ui.actionOpen, SIGNAL(triggered()),
		this, SLOT(openFile()));
	connect(&laserPointListLoader, SIGNAL(loadedLaserPointList(LaserPointList*)),
		this, SLOT(createOpenGLWidget(LaserPointList*)));

// 	connect(ui.actionZoom, SIGNAL(triggered()), this, SLOT(enableZoom()));
// 	connect(ui.actionDrag, SIGNAL(triggered()), this, SLOT(enableDrag()));
// 	connect(ui.actionHeightColor, SIGNAL(triggered()), this, SLOT(setHeightColor()));
// 	connect(ui.actionClassColor, SIGNAL(triggered()), this, SLOT(setClassColor()));



	OpenGLplot * map2D = new OpenGLplot(ui.centralWidget, laserPointList);
	ui.gridLayout->addWidget(map2D, 0, 0);
	map2D->update();
}

LaserMap::~LaserMap()
{
	if (laserPointList != NULL)
		delete laserPointList;
}

/////////////////////////////////////////////////////
////////////////////////SLOTS////////////////////////
/////////////////////////////////////////////////////

void LaserMap::openFile()
{
	QString filename = "C:/Users/Italo/Mis archivos/Universidad/1.-TfG/73.las";
// 	QString filename = QFileDialog::getOpenFileName(this, tr("Open las file"), "", tr("Laser Files(*.las)"));
 	if (filename != NULL)
 	{
		//Lanzar el cargador
		laserPointListLoader.setFilename(filename);		
		laserPointListLoader.start();
	}
}

void LaserMap::createOpenGLWidget(LaserPointList *laserPointListIn)
{
	laserPointList = laserPointListIn;
	//Create Grid layout
	OpenGLplot * map2D = new OpenGLplot(ui.centralWidget, laserPointList);
	//OpenGLplot * map3D = new OpenGLplot(ui.centralWidget, "Hola");
	ui.gridLayout->addWidget(map2D, 0, 0);
	//ui.gridLayout->addWidget(map3D, 0, 1);
	map2D->update();
	//map3D->update();
}

/////////////////////////////////////////////////////
//////////////////PRIVATE FUNCTIONS//////////////////
/////////////////////////////////////////////////////


bool LaserMap::isMapLoaded()
{
	return true;
}