#include "field3dloader.h"

Field3DLoader::Field3DLoader()
	: QThread()
{

}

Field3DLoader::~Field3DLoader()
{

}

void Field3DLoader::run()
{
	emit loaded3DList(laserPointList);
}


void Field3DLoader::setWorkspace(LaserPoint initIn, LaserPoint endIn, LaserPointList* laserPointListIn)
{
	init = initIn;
	end = endIn;
	laserPointList = laserPointListIn;
}