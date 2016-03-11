#ifndef POINTMAPHESTOR_H
#define POINTMAPHESTOR_H
#include "qlist.h"

class PointMapGestor
{
public:
	PointMapGestor();
	~PointMapGestor();
	bool createTree(void);

private:
	
	struct Point{
		float x;
		float y;
		float z;

		bool used = false;
	};
	struct TreeNode{
		//puntos que se almacenan en este nodo
		Point *points; //corregir esto para que sea un array de puntos

		//para guardar el plano que engloba.
		float x0;
		float y0;
		float x1;
		float y1;
		float x2;
		float y2;
		float x3;
		float y3;


		//densidad punto/metro(o cm o lo que sea)
		int density;
	};

	TreeNode treeRoot;

	int minDensity;

	TreeNode createTreeNode(int density,
		float x0,
		float y0,
		float x1,
		float y1,
		float x2,
		float y2,
		float x3,
		float y3);
};

#endif
