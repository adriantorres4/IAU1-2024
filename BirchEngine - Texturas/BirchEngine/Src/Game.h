#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "Map.h"
//#include "Grafo.h"
//#include "Nodo.h"
class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
	//static vector<Nodo*> getCamino();
	static void addTile(int id, int x, int y);
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;
	AEstrella::CoordinateList camino;
	AEstrella::CoordinateList nodosColeccionables;
private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window *window;
	

};