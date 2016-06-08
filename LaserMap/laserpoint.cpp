#include "laserpoint.h"

LaserPoint::LaserPoint()
{

}

LaserPoint::LaserPoint(GLdouble xIn, GLdouble yIn, GLdouble zIn, GLshort intensityIn, GLshort classificationIn, GLdouble rIn,
	GLdouble gIn,
	GLdouble bIn)
{
	x = xIn;
	y = yIn;
	z = zIn;
	intensity = intensityIn;
	classification = classificationIn;
	r = rIn;
	g = gIn;
	b = bIn;
}

LaserPoint::LaserPoint(GLdouble xIn, GLdouble yIn)
{
	x = xIn;
	y = yIn;
}

LaserPoint::~LaserPoint()
{

}

GLdouble LaserPoint::getX()
{
	return x;
}

GLdouble LaserPoint::getY()
{
	return y;
}

GLdouble LaserPoint::getZ()
{
	return z;
}

GLshort LaserPoint::getIntensity()
{
	return intensity;
}

GLshort LaserPoint::getClassification()
{
	return classification;
}

GLdouble LaserPoint::getR()
{
	return r;
}

GLdouble LaserPoint::getG()
{
	return g;
}

GLdouble LaserPoint::getB()
{
	return b;
}
