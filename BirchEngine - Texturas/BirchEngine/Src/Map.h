#pragma once
#include <string>
#include <list>
#include <vector>
//#include "Nodo.h"
#include "Grafo.h"
#include "../AEstrella.h"
//#include "Game.h"

class Map
{
public:
	Map();
	~Map();

	static AEstrella::CoordinateList LoadMap(std::string path,int sizeX, int sizeY, AEstrella::CoordinateList *nodosColeccionables);
	static void LoadMap(std::string path, int sizeX, int sizeY);

private:
	

};