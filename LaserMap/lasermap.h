#ifndef LASERMAP_H
#define LASERMAP_H

#include <QtWidgets/QMainWindow>
#include "ui_lasermap.h"

class LaserMap : public QMainWindow
{
	Q_OBJECT

public:
	LaserMap(QWidget *parent = 0);
	~LaserMap();

private:
	Ui::LaserMapClass ui;
};

#endif // LASERMAP_H
