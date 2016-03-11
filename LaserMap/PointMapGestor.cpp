#include "PointMapGestor.h"

PointMapGestor::PointMapGestor()
{
}


PointMapGestor::~PointMapGestor()
{
}

bool PointMapGestor::createTree(void)
{
	//obtener fichero de puntos
	
	//ordenar? (fijarse en forma de dividir el plano) (guardar maxpunto(x,y) y minpunto(x,y))
	float maxX, maxY, minX, minY;
	//Contar puntos? calcular percentiles?

	//
	QList<Point> *pointList = new QList<Point>();

	//crear raíz con densidad minima
	createTreeNode(minDensity, maxX, maxY, minX, minY);
	//guardar en QList

	//Bucle
		//Sacar nodo de QList
		//Dividir plano según porcentaje de puntos por zona del padre
		//crear hijos
		//Se crearon?
			//enlazar a padre
			//Guardar nodos en Qlist para tratar
	//End bucle
	}


TreeNode PointMapGestor::createTreeNode(int density,
	float x0,
	float y0,
	float x1,
	float y1,
	float x2,
	float y2,
	float x3,
	float y3)
{

}