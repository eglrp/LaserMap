#include "lasermap.h"

LaserMap::LaserMap(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
 	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
// 	connect(ui.actionZoom, SIGNAL(triggered()), this, SLOT(enableZoom()));
// 	connect(ui.actionDrag, SIGNAL(triggered()), this, SLOT(enableDrag()));
// 	connect(ui.actionHeightColor, SIGNAL(triggered()), this, SLOT(setHeightColor()));
// 	connect(ui.actionClassColor, SIGNAL(triggered()), this, SLOT(setClassColor()));



// 	OpenGLplot * map2D = new OpenGLplot(ui.centralWidget, "Hola");
// 	ui.gridLayout->addWidget(map2D, 0, 0);
// 	map2D->update();
}

LaserMap::~LaserMap()
{
	
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

		//Esperar a que termine para luego...

		//Create Grid layout
		OpenGLplot * map2D = new OpenGLplot(ui.centralWidget, "Hola");
		//OpenGLplot * map3D = new OpenGLplot(ui.centralWidget, "Hola");
		ui.gridLayout->addWidget(map2D, 0, 0);
		//ui.gridLayout->addWidget(map3D, 0, 1);
		map2D->update();
		//map3D->update();
	}
}

/////////////////////////////////////////////////////
//////////////////PRIVATE FUNCTIONS//////////////////
/////////////////////////////////////////////////////


bool LaserMap::isMapLoaded()
{
	return true;
}
