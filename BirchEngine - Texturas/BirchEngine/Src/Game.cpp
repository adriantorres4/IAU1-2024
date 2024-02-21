#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

GameObject* player;
GameObject* pikachu;
Map* map;

SDL_Renderer* Game::renderer = nullptr;


/*
SDL_Texture* playerTex;
SDL_Rect srcR, destR;
*/
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

	/*
	SDL_Surface* tmpSurface = IMG_Load("assets/player.png");
	playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	*/
	//playerTex = TextureManager::LoadTexture("assets/player.png", renderer);
	player = new GameObject("assets/player.png", 0, 0);
	pikachu = new GameObject("assets/pikachu_2.png", 50, 50);
	map = new Map();


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
	default:
		break;
	}
}
//---------------------------------------------------------------------------
void Game::update()
{
	player->Update();
	pikachu->Update();
	//map->LoadMap();
}
//---------------------------------------------------------------------------
void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();

	player->Render();
	pikachu->Render();
	SDL_RenderPresent(renderer);

}
//---------------------------------------------------------------------------
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}