#ifndef LASERPOINTLISTLOADER_H
#define LASERPOINTLISTLOADER_H

#include <QThread>
#include "LaserPointList.h"
#include "laserpoint.h"
#include <fstream>  // std::ifstream
#include <iostream>
#include <liblas/liblas.hpp>

class LaserPointListLoader : public QThread
{
	Q_OBJECT

public:
	LaserPointListLoader();
	~LaserPointListLoader();
	void setFilename(QString filenameIn);
	virtual void run();

signals:
	void loadingLaserPointList();
	void loadedLaserPointList(LaserPointList laserPointList);

private:
	QString filename;

};

#endif // LASERPOINTLISTLOADER_H
