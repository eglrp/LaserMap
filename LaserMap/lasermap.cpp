#include "lasermap.h"

LaserMap::LaserMap(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(this, SIGNAL(fileSelected(QString)), ui.openGLplot, SLOT(paintFileLAS(QString)));
	
	ui.openGLplot->update();
}

LaserMap::~LaserMap()
{
	
}

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
		//http://www.liblas.org/tutorial/cpp.html#applying-filters-to-a-reader-to-extract-specified-classes
// 	http://www.liblas.org/doxygen/classliblas_1_1Point.html#details

	
		emit fileSelected(filename);
	}
}
