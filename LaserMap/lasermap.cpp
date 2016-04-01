#include "lasermap.h"

LaserMap::LaserMap(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
// 	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
// 	connect(ui.actionZoom, SIGNAL(triggered()), this, SLOT(enableZoom()));
// 	connect(ui.actionDrag, SIGNAL(triggered()), this, SLOT(enableDrag()));
// 	connect(ui.actionHeightColor, SIGNAL(triggered()), this, SLOT(setHeightColor()));
// 	connect(ui.actionClassColor, SIGNAL(triggered()), this, SLOT(setClassColor()));
	ui.openGLplot->update();

// 	setLayout(new QGridLayout);
// 	QGridLayout *mainLayout = new QGridLayout;
// 	OpenGLplot *openGLplot1 = new OpenGLplot(ui.centralWidget, "Hola");
// 	mainLayout->addWidget(openGLplot1);
// 	ui.centralWidget->setLayout(mainLayout);
	
}

LaserMap::~LaserMap()
{
	
}

/////////////////////////////////////////////////////
////////////////////////SLOTS////////////////////////
/////////////////////////////////////////////////////

void LaserMap::openFile()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open las file"), "", tr("Laser Files(*.las)"));
	if (filename != NULL)
	{
 		QString filename;
// 	
// 		std::ifstream ifs;
// 		ifs.open(filename.toStdString(), std::ios::in | std::ios::binary);
// 		liblas::ReaderFactory f;
// 		liblas::Reader reader = f.CreateWithStream(ifs);
// 	
	
	}
}

/////////////////////////////////////////////////////
//////////////////PRIVATE FUNCTIONS//////////////////
/////////////////////////////////////////////////////


bool LaserMap::isMapLoaded()
{
	return true;
}
