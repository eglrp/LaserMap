#ifndef LASERPOINTLISTLOADER_H
#define LASERPOINTLISTLOADER_H

#include <QThread>
#include "LaserPointList.h"
#include "laserpoint.h"
#include <liblas/liblas.hpp>

class LaserPointListLoader : public QThread
{
	Q_OBJECT

public:
	LaserPointListLoader();
	~LaserPointListLoader();
	virtual void run();
	void setWorkspace(QString filename, LaserPointList* laserPointListIn);

signals:
	void loadingLaserPointList(QString message, int barPercent);
	void loadedLaserPointList();

private:
	LaserPointList* laserPointList;
	QString filename;

};

#endif // LASERPOINTLISTLOADER_H
