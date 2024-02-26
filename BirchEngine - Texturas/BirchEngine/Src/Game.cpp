#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "ECS.h"
#include "Components.h"

GameObject* player;
GameObject* pikachu;
GameObject* col1;
GameObject* col2;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

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

	
	player = new GameObject("assets/player.png", 0, 0);
	pikachu = new GameObject("assets/pikachu_2.png", 50, 50);
	col1 = new GameObject("assets/coleccionable1.png", 100, 100);
	col2 = new GameObject("assets/coleccionable2.png", 150, 150);

	map = new Map();
	newPlayer.addComponent<PositionComponent>();


}
//---------------------------------------------------------------------------
void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) 
		{
		case SDLK_w:
			player->setY(player->getY() - 10);// Move up
			break;
		case SDLK_s:
			player->setY(player->getY() + 10); // Move down
			break;
		case SDLK_a:
			player->setX(player->getX() - 10); // Move left
			break;
		case SDLK_d:
			player->setX(player->getX() + 10); // Move right
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
//---------------------------------------------------------------------------
void Game::update()
{
	player->Update();
	pikachu->Update();
	col1->Update();
	col2->Update();
	
	manager.update();
	std::cout << newPlayer.getComponent<PositionComponent>().x() << ", " << newPlayer.getComponent<PositionComponent>().y() << std::endl;
}
//---------------------------------------------------------------------------
void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();

	player->Render();
	pikachu->Render();
	col1->Render();
	col2->Render();
	SDL_RenderPresent(renderer);

}
//---------------------------------------------------------------------------
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}