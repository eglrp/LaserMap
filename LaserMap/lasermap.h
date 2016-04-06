#ifndef LASERMAP_H
#define LASERMAP_H

#include <QtWidgets/QMainWindow>
#include "ui_lasermap.h"
#include "qfiledialog.h"
#include <QList>
#include <liblas/liblas.hpp>
#include "OpenGLplot.h"
#include "LaserPointList.h"

class LaserMap : public QMainWindow
{
	Q_OBJECT

public:
	LaserMap(QWidget *parent = 0);
	~LaserMap();

signals:
	void fileSelected(QString filename);

private:
	Ui::LaserMapClass ui;
	LaserPointList laserPointList;
	bool isMapLoaded();

private slots:
	void openFile();
};

#endif // LASERMAP_H
