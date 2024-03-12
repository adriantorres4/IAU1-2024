//#include "Nodo.h"
#include "Map.h"
#include "Game.h"
#include <fstream>

//#include "Grafo.h"
#include <list>
#include <vector>
#include "Grafo.h"

using namespace std;
static void  setNodosAdyacentesIzq(list<Nodo>::iterator& it, Nodo& nodoAux, Nodo& nodoActual) {
	advance(it, -1);
	nodoAux = *it;
	nodoActual.agregarAdyacente(nodoAux);
	advance(it, 1);
}
static void setNodosAdyacentesDown(list<Nodo>::iterator& it, Nodo& nodoAux, Nodo& nodoActual) {
	advance(it, 16);
	nodoAux = *it;
	nodoActual.agregarAdyacente(nodoAux);
	advance(it, -16);
}
static void setNodosAdyacentesUp(list<Nodo>::iterator& it, Nodo& nodoAux, Nodo& nodoActual) {
	advance(it, -16);
	nodoAux = *it;
	nodoActual.agregarAdyacente(nodoAux);
	advance(it, 16);
}
static void  setNodosAdyacentesDer(list<Nodo>::iterator& it, Nodo& nodoAux, Nodo& nodoActual) {
	advance(it, 1);
	nodoAux = *it;
	nodoActual.agregarAdyacente(nodoAux);
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
void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);
	int idCasilla = 1;
	list<Nodo> listaNodos;
	Nodo nodoAux;
	Nodo nodoActual;
	int numNodos = 1024;
	int idTipoCasilla;
	Grafo grafo;
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			idTipoCasilla = atoi(&tile);
			Nodo nodo = Nodo(x * 16, y * 16, idTipoCasilla, idCasilla);
			listaNodos.push_back(nodo);
			Game::addTile(idTipoCasilla, x * 16, y * 16);
			mapFile.ignore();
			idCasilla++;
		}
	}
	for (list<Nodo>::iterator it = listaNodos.begin(); it != listaNodos.end(); it++) {
		nodoAux = *it;
		nodoActual = *it;
		if (nodoAux.getY() == 240 && nodoAux.getX() == 240) {
			grafo.agregarNodo(nodoActual);
		}
		else if (nodoAux.getX() == 240) {
			setNodosAdyacentesDown(it, nodoAux, nodoActual);
			grafo.agregarNodo(nodoActual);
		}
		else if (nodoAux.getY() == 240) {
			setNodosAdyacentesDer(it,nodoAux,nodoActual);
			grafo.agregarNodo(nodoActual);
		}
		else {
			setNodosAdyacentesDer(it, nodoAux, nodoActual);
			setNodosAdyacentesDown(it, nodoAux, nodoActual);
			grafo.agregarNodo(nodoActual);
		}

		//Casilla de la esquina superior izquierda
		//if (nodoAux.getValorCasilla() == 1) {
		//	setNodosAdyacentesDer(it, nodoAux, nodoActual);
		//	setNodosAdyacentesDown(it, nodoAux, nodoActual);
		//	grafo.agregarNodo(nodoActual);
		//}
		////Casilla de la esquina superior derecha
		//else if (nodoActual.getY() <= 0 && nodoActual.getX() == 992) {
		//	setNodosAdyacentesIzq(it, nodoAux, nodoActual);
		//	setNodosAdyacentesDown(it, nodoAux, nodoActual);
		//	grafo.agregarNodo(nodoActual);
		//}
		////Casillas sobrantes de la primer fila
		//else if (nodoActual.getY() <= 0 && nodoActual.getX() != 992 && nodoActual.getX() !=0) {
		//	setNodosAdyacentesIzq(it, nodoAux, nodoActual);
		//	setNodosAdyacentesDown(it, nodoAux, nodoActual);
		//	setNodosAdyacentesDer(it, nodoAux, nodoActual);
		//	grafo.agregarNodo(nodoActual);
		//}
		////Casillas de la primer columna
		//else if (nodoActual.getY() != 0 && nodoActual.getX() == 0 && nodoActual.getY() != 992) {
		//	setNodosAdyacentesDer(it, nodoAux, nodoActual);
		//	setNodosAdyacentesDown(it, nodoAux, nodoActual);
		//	setNodosAdyacentesUp(it, nodoAux, nodoActual);
		//	grafo.agregarNodo(nodoActual);
		//}
		////Casilla de la esquina inferior izquierda
		//else if (nodoActual.getY() == 992 && nodoActual.getX() == 0) {
		//	setNodosAdyacentesDer(it, nodoAux, nodoActual);
		//	setNodosAdyacentesUp(it, nodoAux, nodoActual);
		//	grafo.agregarNodo(nodoActual);
		//}
		////Casillas de la ultima fila, sin contar la casilla hasta el final de la derecha
		//else if (nodoActual.getY() == 992 && nodoActual.getX() != 992 && nodoActual.getX()!=0) {
		//	setNodosAdyacentesIzq(it, nodoAux, nodoActual);
		//	setNodosAdyacentesDer(it, nodoAux, nodoActual);
		//	setNodosAdyacentesUp(it, nodoAux, nodoActual);
		//	grafo.agregarNodo(nodoActual);
		//}
		////Casilla de la esquina inferior derecha
		//else if (nodoActual.getY() == 992 && nodoActual.getX() == 992) {
		//	setNodosAdyacentesIzq(it, nodoAux, nodoActual);
		//	setNodosAdyacentesUp(it, nodoAux, nodoActual);
		//	grafo.agregarNodo(nodoActual);
		//}
		////Casillas de la ultima columna
		//else if (nodoActual.getX() == 992 && nodoActual.getY() != 992 && nodoActual.getY() != 0) {
		//	setNodosAdyacentesIzq(it, nodoAux, nodoActual);
		//	setNodosAdyacentesUp(it, nodoAux, nodoActual);
		//	setNodosAdyacentesDown(it, nodoAux, nodoActual);
		//	grafo.agregarNodo(nodoActual);
		//}
		////Casillas del centro del mapa
		//else {
		//	setNodosAdyacentesUp(it, nodoAux, nodoActual);
		//	setNodosAdyacentesDer(it, nodoAux, nodoActual);
		//	setNodosAdyacentesIzq(it, nodoAux, nodoActual);
		//	setNodosAdyacentesDown(it, nodoAux, nodoActual);
		//	grafo.agregarNodo(nodoActual);
		//}
	}
	Nodo nodoOrigen, nodoDestino;
	nodoOrigen.copia(grafo.buscarNodo(0, 0));
	nodoDestino.copia(grafo.buscarNodo(32, 16));
	// Ejecutamos el algoritmo de profundidad
	Grafo grafoAuxiliar = grafo;
	vector<Nodo> camino = grafo.algoritmoProfundidad(nodoOrigen, nodoDestino, grafoAuxiliar);

	// Imprimimos el camino encontrado
	if (!camino.empty()) {
		for (Nodo nodo : camino) {
			cout << nodo.getX() << "," << nodo.getY() << endl;
		}
	}
	else {
		cout << "No se encontró un camino" << endl;
	}
	mapFile.close();

}


//---------------------------------------------------------------------------

