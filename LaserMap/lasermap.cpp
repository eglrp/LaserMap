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
// 	connect(ui.actionHeightColor, SIGNAL(triggered()), this, SLOT(setHeightColor()));
// 	connect(ui.actionClassColor, SIGNAL(triggered()), this, SLOT(setClassColor()));


	laserPointListLoader.setFilename("C:/Users/Italo/Mis archivos/Universidad/1.-TfG/73.las");
	laserPointListLoader.start();
}

LaserMap::~LaserMap()
{
	if (laserPointList != NULL)
		delete laserPointList;
	if (map2D != NULL)
		delete map2D;
	if (map3D != NULL)
		delete map3D;
}

/////////////////////////////////////////////////////
////////////////////////SLOTS////////////////////////
/////////////////////////////////////////////////////

void LaserMap::openFile()
{
 	QString filename = QFileDialog::getOpenFileName(this, tr("Open las file"), "", tr("Laser Files(*.las)"));
 	if (filename != NULL)
 	{
		laserPointListLoader.setFilename(filename);		
		laserPointListLoader.start();
	}
}

void LaserMap::createOpenGLWidget(LaserPointList *laserPointListIn)
{
	laserPointList = laserPointListIn;
	if (map2D == NULL)
	{
		map2D = new OpenGLplot(ui.centralWidget, laserPointList);
		//OpenGLplot * map3D = new OpenGLplot(ui.centralWidget, laserPointList);
		ui.gridLayout->addWidget(map2D, 0, 0);
		//ui.gridLayout->addWidget(map3D, 0, 1);
		map2D->update();
		//map3D->update();
		connect(ui.actionZoom, SIGNAL(triggered()), map2D, SLOT(enableZoom()));
		connect(ui.actionDrag, SIGNAL(triggered()), map2D, SLOT(enableDrag()));
	}
	
}

/////////////////////////////////////////////////////
//////////////////PRIVATE FUNCTIONS//////////////////
/////////////////////////////////////////////////////
