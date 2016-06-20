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
	GLdouble xMin;
	GLdouble xMax;
	GLdouble yMin;
	GLdouble yMax;
	if (init.getX() > end.getX())
	{
		xMax = init.getX();
		xMin = end.getX();
	}
	else
	{
		xMax = end.getX();
		xMin = init.getX();
	}
	if (init.getY() > end.getY())
	{
		yMax = init.getY();
		yMin = end.getY();
	}
	else
	{
		yMax = end.getY();
		yMin = init.getY();
	}
	QList<LaserPoint> *pointList = laserPointList->getList();
	*laserPointList3D = LaserPointList(xMin, xMax, yMin, yMax);

	laserPointList3D->zMax = laserPointList->zMin;
	laserPointList3D->zMin = laserPointList->zMax;

	int percent = 0;
	int numPoints = pointList->size();
	for (int i = 0; i < numPoints; i++)
	{
		LaserPoint p = pointList->at(i);
		if (p.getX() > xMin &&
			p.getX() < xMax &&
			p.getY() > yMin &&
			p.getY() < yMax)
		{
			laserPointList3D->add(p);
			if (p.getZ() > laserPointList3D->zMax)
			{
				laserPointList3D->zMax = p.getZ();
			}
			else if (p.getZ() < laserPointList3D->zMin)
				laserPointList3D->zMin = p.getZ();
		}

		//percent for loadBar
		int newPercent = (i / (float)numPoints) * 100;
		if (newPercent > (percent + 2))
		{
			percent = newPercent;
			emit loading3DList(" Leyendo fichero LAS...", percent);
		}
	}
	laserPointList3D->intensityMin = laserPointList->intensityMin;
	laserPointList3D->intensityMax = laserPointList->intensityMax;
	laserPointList3D->intensityLength = laserPointList->intensityLength;

	emit loading3DList(" Trasladando puntos al centro...", 100);
	laserPointList3D->zLength = laserPointList3D->zMax - laserPointList3D->zMin;
	laserPointList3D->translateToCenter();

	emit loaded3DList();
}


void Field3DLoader::setWorkspace(LaserPoint initIn, LaserPoint endIn, LaserPointList* laserPointListIn, LaserPointList* laserPointList3DIn)
{
	init = initIn;
	end = endIn;
	laserPointList = laserPointListIn;
	laserPointList3D = laserPointList3DIn;
}