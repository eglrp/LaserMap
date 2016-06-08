#include "laserpoint.h"

LaserPoint::LaserPoint()
{

}

LaserPoint::LaserPoint(GLdouble xIn, GLdouble yIn, GLdouble zIn, GLshort intensityIn, GLshort classificationIn)

{
	x = xIn;
	y = yIn;
	z = zIn;
	intensity = intensityIn;
	classification = classificationIn;
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

GLshort LaserPoint::getR()
{
	return r;
}

GLshort LaserPoint::getG()
{
	return g;
}

GLshort LaserPoint::getB()
{
	return b;
}

LaserPoint LaserPoint::generateCopy()
{
	return LaserPoint(x, y, z, intensity, classification);
}
