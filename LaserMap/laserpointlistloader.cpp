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
	emit loadingLaserPointList();
	std::ifstream ifs;
	ifs.open("C:/Users/Italo/Mis archivos/Universidad/1.-TfG/73.las", std::ios::in | std::ios::binary);
	if (ifs.is_open())
	{
		liblas::ReaderFactory f;
		liblas::Reader reader = f.CreateWithStream(ifs);
		liblas::Header const &header = reader.GetHeader();
		LaserPointList *laserPointList = new LaserPointList(header.GetMinX(), header.GetMaxX(),
			header.GetMinY(), header.GetMaxY(),
			header.GetMinZ(), header.GetMaxZ());

		//Read points
		UINT32 numPoints = header.GetPointRecordsCount();
		for (int i = 0; i < numPoints; i++)
		{
			reader.ReadNextPoint();
			liblas::Point const &p = reader.GetPoint();
			laserPointList->add(LaserPoint(p.GetX(), p.GetY(), p.GetZ(), p.GetIntensity(), p.GetClassification().GetClass()) );
		}
		emit loadedLaserPointList(laserPointList);
	}
}

void LaserPointListLoader::setFilename(QString filenameIn)
{
	filename = filenameIn;
}
