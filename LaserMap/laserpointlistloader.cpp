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
	ifs.open(filename.toStdString(), std::ios::in | std::ios::binary);
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
		GLdouble R;
		GLdouble G;
		GLdouble B;
		for (int i = 0; i < numPoints; i++)
		{
			reader.ReadNextPoint();
			liblas::Point const &p = reader.GetPoint();
			liblas::Color color = p.GetColor();
			R = color.GetRed() / (GLdouble)65535;
			G = color.GetGreen() / (GLdouble)65535;
			B = color.GetBlue() / (GLdouble)65535;
			laserPointList->add(LaserPoint(p.GetX(), p.GetY(), p.GetZ(), p.GetIntensity(), p.GetClassification().GetClass(), R, G, B));
		}
		emit loadedLaserPointList(laserPointList);
	}
}

void LaserPointListLoader::setFilename(QString filenameIn)
{
	filename = filenameIn;
}
