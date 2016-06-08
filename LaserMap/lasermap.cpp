#include "lasermap.h"

LaserMap::LaserMap(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//File loader connections
 	connect(ui.actionOpen, SIGNAL(triggered()),
		this, SLOT(openFile()));
	qRegisterMetaType<LaserPointList>("LaserPointList");
	connect(&laserPointListLoader, SIGNAL(loadedLaserPointList(LaserPointList)),
		this, SLOT(createOpenGL2D(LaserPointList)));
	connect(&fiel3DLoader, SIGNAL(loaded3DList(LaserPointList)),
		this, SLOT(createOpenGL3D(LaserPointList)));

	////TEST CODE////
 	laserPointListLoader.setFilename("C:/Users/Italo/Mis archivos/Universidad/1.-TfG/73.las");
 	laserPointListLoader.start();
}

LaserMap::~LaserMap()
{
	
	if (map2D != NULL)
		delete map2D;
	if (map3D != NULL)
		delete map3D;
	if (window3D != NULL)
		delete window3D;
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

void LaserMap::createOpenGL2D(LaserPointList laserPointListIn)
{
	laserPointList = laserPointListIn;
	if (map2D != NULL){
		disconnect(ui.actionZoom, SIGNAL(triggered()), map2D, SLOT(enableZoom()));
		disconnect(ui.actionDrag, SIGNAL(triggered()), map2D, SLOT(enableDrag()));
		disconnect(ui.action3D, SIGNAL(triggered()), map2D, SLOT(enable3D()));
		disconnect(ui.actionHeightColor, SIGNAL(triggered()), map2D, SLOT(setHeightColor()));
		disconnect(ui.actionClassColor, SIGNAL(triggered()), map2D, SLOT(setClassColor()));
		disconnect(map2D, SIGNAL(model3Dselected(LaserPoint, LaserPoint)), this, SLOT(create3DField(LaserPoint, LaserPoint)));
		delete map2D;
	}
	map2D = new OpenGL2D(ui.centralWidget, &laserPointList);
	ui.gridLayout->addWidget(map2D);
	map2D->update();
	connect(ui.actionZoom, SIGNAL(triggered()), map2D, SLOT(enableZoom()));
	connect(ui.actionDrag, SIGNAL(triggered()), map2D, SLOT(enableDrag()));
	connect(ui.action3D, SIGNAL(triggered()), map2D, SLOT(enable3D()));
	connect(ui.actionHeightColor, SIGNAL(triggered()), map2D, SLOT(setHeightColor()));
	connect(ui.actionClassColor, SIGNAL(triggered()), map2D, SLOT(setClassColor()));
	connect(map2D, SIGNAL(model3Dselected(LaserPoint, LaserPoint)), this, SLOT(create3DField(LaserPoint, LaserPoint)));
}

void LaserMap::createOpenGL3D(LaserPointList laserPointListIn)
{
	//laserPointListIn.translateToCenter();
	if (map3D != NULL)
		delete map3D;
	if (window3D != NULL)
		delete window3D;
	//laserPointList3D = laserPointListIn;
	window3D = new QMainWindow();
	map3D = new OpenGL3D(window3D/*, &laserPointList3D*/);
	window3D->setCentralWidget(map3D);
	map3D->update();
	window3D->show();
}

void LaserMap::create3DField(LaserPoint init, LaserPoint end)
{
	fiel3DLoader.setWorkspace(init, end, &laserPointList);
	fiel3DLoader.start();
}

/////////////////////////////////////////////////////
//////////////////PRIVATE FUNCTIONS//////////////////
/////////////////////////////////////////////////////


