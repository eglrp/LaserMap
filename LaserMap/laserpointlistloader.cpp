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
	emit loadingLaserPointList("Cargando fichero LAS...", 0);
	std::ifstream ifs;
	ifs.open(filename.toStdString(), std::ios::in | std::ios::binary);
	if (ifs.is_open())
	{
		liblas::ReaderFactory f;
		liblas::Reader reader = f.CreateWithStream(ifs);
		liblas::Header const &header = reader.GetHeader();
		*laserPointList = LaserPointList(header.GetMinX(), header.GetMaxX(),
			header.GetMinY(), header.GetMaxY(),
			header.GetMinZ(), header.GetMaxZ());

		//Read points
		UINT32 numPoints = header.GetPointRecordsCount();
		GLdouble R;
		GLdouble G;
		GLdouble B;
		int maxIntensity = 0;
		int minIntensity = 2147483647;
		int percent = 0;
		for (int i = 0; i < numPoints; i++)
		{
			reader.ReadNextPoint();
			liblas::Point const &p = reader.GetPoint();
			liblas::Color color = p.GetColor();
			R = color.GetRed() / (GLdouble)65535;
			G = color.GetGreen() / (GLdouble)65535;
			B = color.GetBlue() / (GLdouble)65535;
			laserPointList->add(LaserPoint(p.GetX(), p.GetY(), p.GetZ(), p.GetIntensity(), p.GetClassification().GetClass(), R, G, B));
			if (minIntensity > p.GetIntensity())
				minIntensity = p.GetIntensity();
			if (maxIntensity < p.GetIntensity())
				maxIntensity = p.GetIntensity();

			//percent for loadBar
			int newPercent = (i /(float) numPoints) * 100;
			if (newPercent > (percent + 2))
			{
				percent = newPercent;
				emit loadingLaserPointList(" Cargando fichero LAS...", percent);
			}
		}
		laserPointList->intensityMin = minIntensity;
		laserPointList->intensityMax = maxIntensity;
		laserPointList->intensityLength = maxIntensity - minIntensity;
		emit loadedLaserPointList();
	}
}

void LaserPointListLoader::setWorkspace(QString filenameIn, LaserPointList* laserPointListIn)
{
	filename = filenameIn;
	laserPointList = laserPointListIn;
}
