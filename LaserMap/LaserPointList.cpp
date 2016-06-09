#include "LaserPointList.h"


LaserPointList::LaserPointList(GLdouble xMinIn, GLdouble xMaxIn, GLdouble yMinIn, GLdouble yMaxIn, GLdouble zMinIn, GLdouble zMaxIn)
{
	xMinInit = xMin = xMinIn;
	xMaxInit = xMax = xMaxIn;
	xLengthInit = xLength = xMax - xMin;
	yMinInit = yMin = yMinIn;
	yMaxInit = yMax = yMaxIn;
	yLengthInit = yLength = yMax - yMin;
	zMin = zMinIn;
	zMax = zMaxIn;
	zLength = zMax - zMin;
	ratioMap = xLength / yLength;
	mapCenter[0] = xMin + xLength / 2.0;
	mapCenter[1] = yMin + yLength / 2.0;
	percent = 1.0;
}

LaserPointList::LaserPointList()
{

}

LaserPointList::LaserPointList(GLdouble xMinIn, GLdouble xMaxIn, GLdouble yMinIn, GLdouble yMaxIn)
{
	xMinInit = xMin = xMinIn;
	xMaxInit = xMax = xMaxIn;
	xLengthInit = xLength = xMax - xMin;
	yMinInit = yMin = yMinIn;
	yMaxInit = yMax = yMaxIn;
	yLengthInit = yLength = yMax - yMin;
	ratioMap = xLength / yLength;
	mapCenter[0] = xMin + xLength / 2.0;
	mapCenter[1] = yMin + yLength / 2.0;
	percent = 1.0;
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

void LaserPointList::translateToCenter()
{
	/*GLdouble xTranslation = (xMaxInit + xMinInit) / 2;
	GLdouble yTranslation = (yMaxInit + yMinInit) / 2;
	GLdouble zTranslation = (zMax + zMin) / 2;

	xMinInit -= xTranslation;
	xMaxInit -= xTranslation;
	yMinInit -= yTranslation;
	yMaxInit -= yTranslation;
	zMin -= zTranslation;
	zMax -= zTranslation;

	QList<LaserPoint> newList;
	for (int i = 0; i < pointList.size(); i++)
	{
		LaserPoint p = pointList.at(i);
		newList.append(LaserPoint(p.getX() - xTranslation, p.getY() - yTranslation, p.getZ() - zTranslation, p.getIntensity(), p.getClassification()));
	}
	pointList = newList;
	resetData();*/
}