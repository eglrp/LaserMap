#include "lasermap.h"

LaserMap::LaserMap(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//File loader connections (LaserPointListLoader)
 	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(closeFile()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(&laserPointListLoader, SIGNAL(loadedLaserPointList()), this, SLOT(createOpenGL2D()));
	connect(&laserPointListLoader, SIGNAL(loadingLaserPointList(QString, int)), this, SLOT(writeMessageBar(QString, int)));
	connect(&fiel3DLoader, SIGNAL(loaded3DList()), this, SLOT(createOpenGL3D()));
	connect(&fiel3DLoader, SIGNAL(loading3DList(QString, int)), this, SLOT(writeMessageBar(QString, int)));

	//Button groups
	toolActions = new QActionGroup(this);
	toolActions->addAction(ui.action3D);
	toolActions->addAction(ui.actionDistance);
	toolActions->addAction(ui.actionDrag);
	toolActions->addAction(ui.actionZoom);
	toolActions->setExclusive(true);

	colorActions = new QActionGroup(this);
	colorActions->addAction(ui.actionClassColor);
	colorActions->addAction(ui.actionHeightColor);
	colorActions->addAction(ui.actionRealColor);
	colorActions->addAction(ui.actionIntensityColor);
	colorActions->setExclusive(true);

	//Info labels
	localizationLabel = new QLabel();
	localizationLabel->setAlignment(Qt::AlignLeft);
	localizationLabel->setText("X = ..  Y = ..  Zoom = ..");
	localizationLabel->setMinimumWidth(220);
	ui.statusBar->addWidget(localizationLabel);
	statusLabel = new QLabel();
	statusLabel->setAlignment(Qt::AlignLeft);
	statusLabel->setText("Listo");
	statusLabel->setMinimumWidth(220);
	ui.statusBar->addWidget(statusLabel);
}

LaserMap::~LaserMap()
{
	delete toolActions;
	delete colorActions;
	if (map2D != NULL)
		delete map2D;
	if (map3D != NULL)
		delete map3D;
	if (window3D != NULL)
		delete window3D;
	if (progressBar != NULL)
		delete progressBar;
	delete statusLabel;
}

/////////////////////////////////////////////////////
////////////////////////SLOTS////////////////////////
/////////////////////////////////////////////////////

void LaserMap::openFile()
{
	//QFileDialog
 	QString filename = QFileDialog::getOpenFileName(this, tr("Open las file"), "", tr("Laser Files(*.las)"));

 	if (filename != NULL)
 	{
		//Window clean (if needed)
		if (map2D != NULL){
			delete map2D;
		}
		//Thread start
		laserPointListLoader.setWorkspace(filename, &laserPointList);
		laserPointListLoader.start();
	}
}

void LaserMap::closeFile()
{
	if (map2D != NULL){
		delete map2D;
		map2D = NULL;
		if (map3D != NULL)
		{
			delete map3D;
			map3D = NULL;
		}
		if (window3D != NULL)
		{
			delete window3D;
			window3D = NULL;
		}

		colorActions->checkedAction()->setChecked(false);
		toolActions->checkedAction()->setChecked(false);
		localizationLabel->setText("X = ..  Y = ..  Zoom = ..");
		statusLabel->setText(" Fichero LAS cerrado.");
	}
}

void LaserMap::createOpenGL2D()
{
	//Clean Info Label and loadBar after LaserPointListLoader use
	writeMessageBar("", 100);
	//Create new QOpenGLWidget
	map2D = new OpenGL2D(ui.centralWidget, &laserPointList);
	ui.gridLayout->addWidget(map2D);
	map2D->update();
	//Connect it to buttons
	connect(ui.actionZoom, SIGNAL(triggered()), map2D, SLOT(enableZoom()));
	connect(ui.actionDrag, SIGNAL(triggered()), map2D, SLOT(enableDrag()));
	connect(ui.action3D, SIGNAL(triggered()), map2D, SLOT(enable3D()));
	connect(ui.actionDistance, SIGNAL(triggered()), map2D, SLOT(enableDistance()));

	connect(ui.actionHeightColor, SIGNAL(triggered()), map2D, SLOT(setHeightColor()));
	connect(ui.actionClassColor, SIGNAL(triggered()), map2D, SLOT(setClassColor()));
	connect(ui.actionRealColor, SIGNAL(triggered()), map2D, SLOT(setRealColor()));
	connect(ui.actionIntensityColor, SIGNAL(triggered()), map2D, SLOT(setIntensityColor()));

	//Connect it to InfoLabel SLOTs
	connect(map2D, SIGNAL(postMessage(QString)), this, SLOT(writeMessage(QString)));
	connect(map2D, SIGNAL(model3Dselected(LaserPoint, LaserPoint)), this, SLOT(create3DField(LaserPoint, LaserPoint)));
	connect(map2D, SIGNAL(mouseMoved(int, int)), this, SLOT(writeLocalization(int, int)));

	//Enable default actions
	ui.actionZoom->setChecked(true);
	ui.actionHeightColor->setChecked(true);
}

void LaserMap::createOpenGL3D()
{
	//Clean Info Label and loadBar after Field3DLoader use
	writeMessageBar("", 100);
	//Delete Window 3D (if needed)
	if (map3D != NULL)
		delete map3D;
	if (window3D != NULL)
		delete window3D;
	//Create new Window and QOpenGLWidget
	window3D = new QMainWindow();
	map3D = new OpenGL3D(window3D, &laserPointList3D, colorActions->checkedAction());
	//Connect to color buttons
	connect(ui.actionHeightColor, SIGNAL(triggered()), map3D, SLOT(setHeightColor()));
	connect(ui.actionClassColor, SIGNAL(triggered()), map3D, SLOT(setClassColor()));
	connect(ui.actionRealColor, SIGNAL(triggered()), map3D, SLOT(setRealColor()));
	connect(ui.actionIntensityColor, SIGNAL(triggered()), map3D, SLOT(setIntensityColor()));

	//Show window
	window3D->setCentralWidget(map3D);
	map3D->update();
	window3D->show();
	window3D->setMinimumWidth(400);
	window3D->setMinimumHeight(400);
}

void LaserMap::create3DField(LaserPoint init, LaserPoint end)
{
	//Run Thread
	fiel3DLoader.setWorkspace(init, end, &laserPointList, &laserPointList3D);
	fiel3DLoader.start();
}

void LaserMap::writeMessage(QString message)
{
	statusLabel->setText(message);
}

void LaserMap::writeMessageBar(QString message, int barPercent)
{
	statusLabel->setText(message);
	if (barPercent < 100)
	{
		if (progressBar == NULL)
		{
			progressBar = new QProgressBar();
			progressBar->setMaximumWidth(100);
			progressBar->setMinimumWidth(100);
			progressBar->setMaximumHeight(15);
			progressBar->setMinimumHeight(15);

			progressBar->setAlignment(Qt::AlignCenter);
			progressBar->setMinimum(0);
			progressBar->setMaximum(100);
			ui.statusBar->addWidget(progressBar);
		}
		progressBar->setValue(barPercent);
	}
	//Delete progressBar if load arrived to 100%
	else if (progressBar != NULL)
	{
		delete progressBar;
		progressBar = NULL;
	}
}

void LaserMap::writeLocalization(int x, int y)
{
	QString message(" X = ");
	message += QString::number(x);
	message += "m Y = ";
	message += QString::number(y);
	message += "m Zoom = ";
	int zoom = (1 - laserPointList.percent) * 100;
	message += QString::number(zoom);
	message += "%";
	localizationLabel->setText(message);
}
