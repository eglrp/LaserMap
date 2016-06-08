#ifndef LASERPOINT_H
#define LASERPOINT_H
#include <QtOpenGL>

class LaserPoint
{

public:
	LaserPoint(GLdouble xIn,
		GLdouble yIn,
		GLdouble zIn,
		GLshort intensityIn,
		GLshort classificationIn);
	LaserPoint(GLdouble xIn,
		GLdouble yIn);
	LaserPoint();
	~LaserPoint();
	LaserPoint generateCopy();
	GLdouble getX();
	GLdouble getY();
	GLdouble getZ();
	GLshort getIntensity();
	GLshort getClassification();
	GLshort getR();
	GLshort getG();
	GLshort getB();

private:
	GLdouble x;
	GLdouble y;
	GLdouble z;
	GLshort intensity;
	GLshort classification;
	GLshort r;
	GLshort g;
	GLshort b;

};

#endif // LASERPOINT_H
