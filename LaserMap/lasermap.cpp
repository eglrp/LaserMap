#include "lasermap.h"

LaserMap::LaserMap(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.openGLplot->update();
}

LaserMap::~LaserMap()
{
	
}
