#ifndef LASERPOINTLIST_H
#define LASERPOINTLIST_H
#include <QList>
#include "LaserPoint.h"

class LaserPointList
{
public:
	LaserPointList(GLdouble xMinIn, GLdouble xMaxIn, GLdouble yMaxIn, GLdouble yMinIn, GLdouble zMinIn, GLdouble zMaxIn);
	LaserPointList(GLdouble xMinIn, GLdouble xMaxIn, GLdouble yMinIn, GLdouble yMaxIn);
	LaserPointList();
	~LaserPointList();
	void add(LaserPoint point);
	void resetData();
	GLdouble getRatioMap();
	QList<LaserPoint>* getList();
	void translateToCenter();
	GLdouble xMin, xMax, xLength, yMin, yMax, yLength, zMin, zMax, zLength, percent;
	int intensityMin, intensityMax, intensityLength;
	GLdouble mapCenter[2];

private:
	QList<LaserPoint> pointList;
	GLdouble xMinInit, xMaxInit, xLengthInit, yMinInit, yMaxInit, yLengthInit, ratioMap;
};

#endif