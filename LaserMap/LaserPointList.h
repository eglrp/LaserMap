#ifndef LASERPOINTLIST_H
#define LASERPOINTLIST_H
#include <QList>
#include "LaserPoint.h"

class LaserPointList
{
public:
	LaserPointList(GLdouble xMinIn, GLdouble xMaxIn, GLdouble yMaxIn, GLdouble yMinIn, GLdouble zMaxIn, GLdouble zMinIn);
	~LaserPointList();
	void add(LaserPoint point);
	QList<LaserPoint>* getList();

private:
	QList<LaserPoint> pointList;
	GLdouble xMin, xMax, xLength, yMin, yMax, yLength, zMin, zMax, ratioMap;
	GLdouble xMinInit, xMaxInit, xLengthInit, yMinInit, yMaxInit, yLengthInit;
	GLdouble mapCenter[2];
};

#endif