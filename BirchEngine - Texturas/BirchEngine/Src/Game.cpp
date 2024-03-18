#include "Game.h"
#include "TextureManager.h"
#include "ECS/Components.h"
//#include "Map.h"
#include "Vector2D.h"
#include "Collision.h"
#include <iostream>
#include <fstream>
#include <vector>
//#include <iostream>
#include <random>
Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabel : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};


Game::Game()
{}

Game::~Game()
{}
void writeMapToFile(const vector<vector<int>>& map, const string& filename) {
	ofstream outputFile(filename);

	if (outputFile.is_open()) {
		for (const auto& row : map) {
			for (int cell : row) {
				outputFile << cell << " ";
			}
			outputFile << endl;
		}
		cout << "Mapa guardado en " << filename << endl;
		outputFile.close();
	}
	else {
		cerr << "Error al abrir el archivo " << filename << endl;
	}
}

//---------------------------------------------------------------------------
void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	map = new Map();
	//ecs implementacion

	 // Inicializar el generador de números aleatorios con una semilla basada en el tiempo actual
	std::mt19937 rng(std::random_device{}());

	// Definir la distribución de números enteros en el rango [1, 5]
	std::uniform_int_distribution<int> dist(1, 9);
	std::uniform_int_distribution<int> distPisos(1, 2);
	std::uniform_int_distribution<int> distObstaculos(6, 9);
	std::uniform_int_distribution<int> distRand(1, 2);
	int coleccionables = 0;
	int tipoCasilla = 0;
	vector<vector<int>> map;
	vector<int> fila;
	for (int i = 0;i < 10;i++) {
		for (int j = 0; j < 10; j++)
		{
			if (i == 0 || i == 1) {
				tipoCasilla = distPisos(rng);
				fila.push_back(tipoCasilla);
			}
			else if (distRand(rng) == 1) {
				tipoCasilla = distPisos(rng);
				fila.push_back(tipoCasilla);
			}
			else {
				tipoCasilla = distObstaculos(rng);
				fila.push_back(tipoCasilla);
			}


		}
		tipoCasilla = dist(rng);
		if ((tipoCasilla == 3 || tipoCasilla == 4 || tipoCasilla == 5) && coleccionables < 6) {
			coleccionables++;
			fila.push_back(tipoCasilla);
		}
		else {
			fila.push_back(distPisos(rng));
		}
		map.push_back(fila);
		fila.clear();
	}

	// Escribir el mapa en un archivo .map
	writeMapToFile(map, "assets/map1.map");
	this->camino = Map::LoadMap("assets/map.map", 10, 10,&this->nodosColeccionables);
	this->camino = Map::LoadMap("assets/map1.map", 10, 10,&this->nodosColeccionables);

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/pikachu_0.png");
	player.addComponent<KeyBoardController>(this->camino,this->nodosColeccionables);
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);


	wall.addComponent<TransformComponent>(300.f, 300.0f, 40, 20, 1);
	wall.addComponent<SpriteComponent>("assets/coleccionable1.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);
}
//---------------------------------------------------------------------------
void Game::handleEvents()
{


	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}
//---------------------------------------------------------------------------
void Game::update()
{
	manager.update();
	manager.refresh();
	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);

	}

}
//---------------------------------------------------------------------------
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

//---------------------------------------------------------------------------
void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& e : enemies)
	{
		e->draw();
	}

	SDL_RenderPresent(renderer);

}
//---------------------------------------------------------------------------
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::addTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 64, 64, id);
	tile.addGroup(groupMap);
}

//vector<Nodo*> Game::getCamino() {
//	return camino;
//}