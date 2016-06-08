#include "laserpointlistloader.h"

LaserPointListLoader::LaserPointListLoader()
	: QThread()
{
}

LaserPointListLoader::~LaserPointListLoader()
{

}

void LaserPointListLoader::run()
{
	qDebug() << "cargando";
	emit loadingLaserPointList();
	std::ifstream ifs;
	ifs.open(filename.toStdString(), std::ios::in | std::ios::binary);
	if (ifs.is_open())
	{
		liblas::ReaderFactory f;
		liblas::Reader reader = f.CreateWithStream(ifs);
		liblas::Header const &header = reader.GetHeader();
		LaserPointList laserPointList(header.GetMinX(), header.GetMaxX(),
			header.GetMinY(), header.GetMaxY(),
			header.GetMinZ(), header.GetMaxZ());

		//Read points
		UINT32 numPoints = header.GetPointRecordsCount();
		for (int i = 0; i < numPoints; i++)
		{
			reader.ReadNextPoint();
			liblas::Point const &p = reader.GetPoint();
			laserPointList.add(LaserPoint(p.GetX(), p.GetY(), p.GetZ(), p.GetIntensity(), p.GetClassification().GetClass()) );
		}
		emit loadedLaserPointList(laserPointList);
		qDebug() << "cargado";
	}
}

void LaserPointListLoader::setFilename(QString filenameIn)
{
	filename = filenameIn;
}
