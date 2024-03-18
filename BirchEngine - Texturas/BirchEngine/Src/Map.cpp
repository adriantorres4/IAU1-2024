//#include "Nodo.h"
#include "Map.h"
//#include "Game.h"
#include <fstream>

//#include "Grafo.h"
#include <list>
#include <vector>
#include "../AEstrella.h"
#include "Game.h"
//#include "Grafo.h"
//#include "Nodo.h"
//#include "ECS/KeyboardController.h"


using namespace std;
//AEstrella::CoordinateList nodosColeccionables;
static void  setNodosAdyacentesIzq(list<Nodo*>::iterator it, Nodo* nodoAux, Nodo* nodoActual) {
	nodoAux = new Nodo();
	advance(it, -1);
	nodoAux = *it;
	nodoActual->agregarAdyacente(nodoAux);
	advance(it, 1);
}
static void setNodosAdyacentesDown(list<Nodo*>::iterator it, Nodo* nodoAux, Nodo* nodoActual) {
	nodoAux = new Nodo();
	advance(it, 10);
	nodoAux = *it;
	nodoActual->agregarAdyacente(nodoAux);
	advance(it, -10);
}
static void setNodosAdyacentesUp(list<Nodo*>::iterator it, Nodo* nodoAux, Nodo* nodoActual) {
	nodoAux = new Nodo();
	advance(it, -10);
	nodoAux = *it;
	nodoActual->agregarAdyacente(nodoAux);
	advance(it, 10);
}
static void  setNodosAdyacentesDer(list<Nodo*>::iterator it, Nodo* nodoAux, Nodo* nodoActual) {
	nodoAux = new Nodo();
	advance(it, 1);
	nodoAux = *it;
	nodoActual->agregarAdyacente(nodoAux);
	advance(it, -1);
}
//---------------------------------------------------------------------------
Map::Map()
{

}
//---------------------------------------------------------------------------
Map::~Map()
{

}
//---------------------------------------------------------------------------
 void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	char tile;
	std::fstream mapFile;
	mapFile.open(path);
	int idCasilla = 1;
	list<Nodo*> listaNodos;

	int numNodos = 1024;
	int idTipoCasilla;
	Grafo* grafo = new Grafo();
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			idTipoCasilla = atoi(&tile);
			Nodo* nodo = new Nodo(x * 64, y * 64, idTipoCasilla, idCasilla);
			listaNodos.push_back(nodo);
			Game::addTile(idTipoCasilla, x * 64, y * 64);
			mapFile.ignore();
			idCasilla++;
		}
	}
	mapFile.close();
}
//---------------------------------------------------------------------------
AEstrella::CoordinateList Map::LoadMap(std::string path, int sizeX, int sizeY, AEstrella::CoordinateList *nodosColeccionables)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);
	int idCasilla = 1;
	list<Nodo*> listaNodos;

	int numNodos = 1024;
	int idTipoCasilla;
	Grafo* grafo = new Grafo();
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			idTipoCasilla = atoi(&tile);
			Nodo* nodo = new Nodo(x * 64, y * 64, idTipoCasilla, idCasilla);
			listaNodos.push_back(nodo);
			Game::addTile(idTipoCasilla, x * 64, y * 64);
			mapFile.ignore();
			idCasilla++;
		}
	}
	for (list<Nodo*>::iterator it = listaNodos.begin(); it != listaNodos.end(); it++) {
		Nodo* nodoAux = new Nodo();
		Nodo* nodoActual = new Nodo();
		nodoAux = *it;
		nodoActual = *it;
		if (nodoAux->getY() == 576 && nodoAux->getX() == 576) {
			grafo->agregarNodo(nodoActual);
		}
		else if (nodoAux->getX() == 576) {
			setNodosAdyacentesDown(it, nodoAux, nodoActual);
			grafo->agregarNodo(nodoActual);
		}
		else if (nodoAux->getY() == 576) {
			setNodosAdyacentesDer(it, nodoAux, nodoActual);
			grafo->agregarNodo(nodoActual);
		}
		else {
			setNodosAdyacentesDer(it, nodoAux, nodoActual);
			setNodosAdyacentesDown(it, nodoAux, nodoActual);
			grafo->agregarNodo(nodoActual);
		}

		//Casilla de la esquina superior izquierda
	//	if (nodoAux->getValorCasilla() == 1) {
	//		setNodosAdyacentesDer(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDown(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casilla de la esquina superior derecha
	//	else if (nodoActual->getY() <= 0 && nodoActual->getX() == 992) {
	//		setNodosAdyacentesIzq(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDown(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casillas sobrantes de la primer fila
	//	else if (nodoActual->getY() <= 0 && nodoActual->getX() != 992 && nodoActual->getX() !=0) {
	//		setNodosAdyacentesIzq(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDown(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDer(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casillas de la primer columna
	//	else if (nodoActual->getY() != 0 && nodoActual->getX() == 0 && nodoActual->getY() != 992) {
	//		setNodosAdyacentesDer(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDown(it, nodoAux, nodoActual);
	//		setNodosAdyacentesUp(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casilla de la esquina inferior izquierda
	//	else if (nodoActual->getY() == 992 && nodoActual->getX() == 0) {
	//		setNodosAdyacentesDer(it, nodoAux, nodoActual);
	//		setNodosAdyacentesUp(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casillas de la ultima fila, sin contar la casilla hasta el final de la derecha
	//	else if (nodoActual->getY() == 992 && nodoActual->getX() != 992 && nodoActual->getX()!=0) {
	//		setNodosAdyacentesIzq(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDer(it, nodoAux, nodoActual);
	//		setNodosAdyacentesUp(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casilla de la esquina inferior derecha
	//	else if (nodoActual->getY() == 992 && nodoActual->getX() == 992) {
	//		setNodosAdyacentesIzq(it, nodoAux, nodoActual);
	//		setNodosAdyacentesUp(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casillas de la ultima columna
	//	else if (nodoActual->getX() == 992 && nodoActual->getY() != 992 && nodoActual->getY() != 0) {
	//		setNodosAdyacentesIzq(it, nodoAux, nodoActual);
	//		setNodosAdyacentesUp(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDown(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}
	//	//Casillas del centro del mapa
	//	else {
	//		setNodosAdyacentesUp(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDer(it, nodoAux, nodoActual);
	//		setNodosAdyacentesIzq(it, nodoAux, nodoActual);
	//		setNodosAdyacentesDown(it, nodoAux, nodoActual);
	//		grafo->agregarNodo(nodoActual);
	//	}

	}
	Nodo* nodoOrigen, * nodoDestino;
	nodoOrigen = (grafo->buscarNodo(0, 0));
	nodoDestino = (grafo->buscarNodo(96, 96));
	// Ejecutamos el algoritmo de profundidad

	vector<Nodo*> camino = grafo->algoritmoProfundidad(nodoOrigen, nodoDestino);

	// Imprimimos el camino encontrado
	if (!camino.empty()) {
		for (Nodo* nodo : camino) {
			int x = nodo->getX();
			int y = nodo->getY();
			int casilla = nodo->getValorCasilla();
			cout << x << "," << y << " VC: " << casilla << endl;
		}
	}
	else {
		cout << "No se encontró un camino" << endl;
	}
	//KeyBoardController movementController;
	AEstrella::Generator generator;
	generator.setWorldSize({ 33, 33 });
	generator.setHeuristic(AEstrella::Heuristic::manhattan);
	generator.setDiagonalMovement(false);

	/*generator.addCollision({ 5,2 });
	generator.addCollision({ 6,2 });
	generator.addCollision({ 7,2 });
	generator.addCollision({ 8,2 });
	generator.addCollision({ 9,2 });
	generator.addCollision({ 10,2 });
	generator.addCollision({ 11,2 });
	generator.addCollision({ 12,2 });

	generator.addCollision({ 12,3 });
	generator.addCollision({ 12,4 });
	generator.addCollision({ 12,5 });
	generator.addCollision({ 12,6 });
	generator.addCollision({ 12,7 });
	generator.addCollision({ 12,8 });
	generator.addCollision({ 12,9 });
	generator.addCollision({ 12,10 });
	generator.addCollision({ 12,11 });
	generator.addCollision({ 12,12 });

	generator.addCollision({ 11,12 });
	generator.addCollision({ 10,12 });
	generator.addCollision({ 9,12 });
	generator.addCollision({ 8,12 });
	generator.addCollision({ 7,12 });
	generator.addCollision({ 6,12 });
	generator.addCollision({ 5,12 });
	generator.addCollision({ 4,12 });
	generator.addCollision({ 3,12 });
	generator.addCollision({ 2,12 });
	generator.addCollision({ 4,5 });*/

	std::cout << "Generate path ... \n";
	list<Nodo*> listaColeccionables;
	AEstrella::CoordinateList pathPorColeccionable;
	AEstrella::CoordinateList pathFinal;
	int cantColeccionables = 0;
	for (Nodo* nodo : listaNodos) {
		if (nodo->getTipoCasilla() == 6 || nodo->getTipoCasilla() == 7 || nodo->getTipoCasilla() == 8 || nodo->getTipoCasilla() == 9) {
			generator.addCollision({ nodo->getX() / 64,nodo->getY() / 64 });
		}
	}
	for (Nodo* nodo : listaNodos) {
		if (nodo->getTipoCasilla() == 3 || nodo->getTipoCasilla() == 4 || nodo->getTipoCasilla() == 5) {
			listaColeccionables.push_back(nodo);
			nodosColeccionables->push_back({ nodo->getX(),nodo->getY() });
			
		}
	}
	for (Nodo* nodo : listaColeccionables) {
		cantColeccionables++;
		if (cantColeccionables == 1) {
			pathPorColeccionable = generator.findPath({ 0,0 }, { nodo->getX() / 64,nodo->getY() / 64 });
			for (int i = 0;i < pathPorColeccionable.size();i++) {
				pathFinal.push_back(pathPorColeccionable.at(i));
			}
		}
		else {
			pathPorColeccionable = generator.findPath({ pathFinal[0].x,pathFinal[0].y }, { nodo->getX() / 64,nodo->getY() / 64 });
			for (int i = pathPorColeccionable.size() - 1;i >= 0;i--) {
				if (i != pathPorColeccionable.size() - 1)
					pathFinal.insert(pathFinal.begin(), pathPorColeccionable.at(i));
			}
		}
	}
	//AEstrella::CoordinateList pathEstrella = generator.findPath({ 0,0 }, { 32, 32 });

	for (int i = 0;i < pathFinal.size();i++) {
		cout << pathFinal.at(i).x << " " << pathFinal.at(i).y << "\n";
	}
	mapFile.close();
	return pathFinal;
}


//---------------------------------------------------------------------------

