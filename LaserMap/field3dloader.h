#ifndef FIELD3DLOADER_H
#define FIELD3DLOADER_H

#include <QThread>
#include "LaserPointList.h"
#include "laserpoint.h"

class Field3DLoader : public QThread
{
	Q_OBJECT

public:
	Field3DLoader();
	~Field3DLoader();
	void setWorkspace(LaserPoint initIn, LaserPoint endIn, LaserPointList* laserPointListIn, LaserPointList* laserPointList3DIn);
	virtual void run();

signals:
	void loading3DList(QString message, int barPercent);
	void loaded3DList();

private:
	LaserPoint init;
	LaserPoint end;
	LaserPointList* laserPointList;
	LaserPointList* laserPointList3D;
	
};

#endif // FIELD3DLOADER_H
