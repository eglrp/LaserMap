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
	void setWorkspace(LaserPoint initIn, LaserPoint endIn, LaserPointList* laserPointListIn);
	virtual void run();

signals:
	void loading3DList();
	void loaded3DList(LaserPointList *laserPointList);

private:
	LaserPoint init;
	LaserPoint end;
	LaserPointList* laserPointList;
	
};

#endif // FIELD3DLOADER_H
