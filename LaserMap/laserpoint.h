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
		GLshort classificationIn,
		GLdouble rIn,
		GLdouble gIn,
		GLdouble bIn);
	LaserPoint(GLdouble xIn,
		GLdouble yIn);
	LaserPoint();
	~LaserPoint();
	GLdouble getX();
	GLdouble getY();
	GLdouble getZ();
	GLshort getIntensity();
	GLshort getClassification();
	GLdouble getR();
	GLdouble getG();
	GLdouble getB();
	int compareTo(LaserPoint point);

private:
	GLdouble x;
	GLdouble y;
	GLdouble z;
	GLshort intensity;
	GLshort classification;
	GLdouble r;
	GLdouble g;
	GLdouble b;

};

#endif // LASERPOINT_H
