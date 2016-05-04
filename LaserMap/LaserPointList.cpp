#include "LaserPointList.h"


LaserPointList::LaserPointList(GLdouble xMinIn, GLdouble xMaxIn, GLdouble yMinIn, GLdouble yMaxIn, GLdouble zMaxIn, GLdouble zMinIn)
{
	xMinInit = xMin = xMinIn;
	xMaxInit = xMax = xMaxIn;
	xLengthInit = xLength = xMax - xMin;
	yMinInit = yMin = yMinIn;
	yMaxInit = yMax = yMaxIn;
	yLengthInit = yLength = yMax - yMin;
	zMin = zMinIn;
	zMax = zMaxIn;
	ratioMap = xLength / yLength;
	mapCenter[0] = xMin + xLength / 2.0;
	mapCenter[1] = yMin + yLength / 2.0;
	percent = 1.0;
}

LaserPointList::LaserPointList()
{

}


LaserPointList::~LaserPointList()
{
}

void LaserPointList::add(LaserPoint point)
{
	pointList.append(point);
}

QList<LaserPoint>* LaserPointList::getList()
{
	return &pointList;
}

void LaserPointList::resetData()
{
	xMin = xMinInit;
	xMax = xMaxInit;
	xLength = xLengthInit;
	yMin = yMinInit;
	yMax = yMaxInit;
	yLength = yLengthInit;
	mapCenter[0] = xMin + xLength / 2;
	mapCenter[1] = yMin + yLength / 2;
	percent = 1.0;
}

GLdouble LaserPointList::getRatioMap()
{
	return ratioMap;
}
