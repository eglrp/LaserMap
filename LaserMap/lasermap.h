#ifndef LASERMAP_H
#define LASERMAP_H

#include <QtWidgets/QMainWindow>
#include "ui_lasermap.h"
#include "qfiledialog.h"
#include <QList>
#include <liblas/liblas.hpp>

#include "OpenGL2D.h"
#include "LaserPointList.h"
#include "laserpointlistloader.h"
#include "field3dloader.h"

class LaserMap : public QMainWindow
{
	Q_OBJECT

public:
	LaserMap(QWidget *parent = 0);
	~LaserMap();

public slots:
	void createOpenGL2D();
	void createOpenGL3D();
	void create3DField(LaserPoint init, LaserPoint end);

private:
	Ui::LaserMapClass ui;
	QActionGroup* toolActions;
	QActionGroup* colorActions;
	LaserPointList laserPointList;
	LaserPointList laserPointList3D;
	LaserPointListLoader laserPointListLoader;
	Field3DLoader fiel3DLoader;
	OpenGL2D * map2D = NULL;
	QMainWindow * window3D = NULL;
	OpenGL3D * map3D = NULL;
	QLabel* localizationLabel;
	QLabel* statusLabel;
	QProgressBar* progressBar = NULL;

private slots:
	void openFile();
	void closeFile();
	void writeLocalization(int x, int y);
	void writeMessage(QString message);
	void writeMessageBar(QString message, int barPercent);
};

#endif // LASERMAP_H
