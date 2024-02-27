#include "Game.h"
#include "TextureManager.h"
#include "ECS/Components.h"
#include "Map.h"


Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());

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

	map = new Map();
	//ecs implementacion
	player.addComponent<PositionComponent>(100,500);
	player.addComponent<SpriteComponent>("assets/pikachu_0.png");

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
		/*switch (event.key.keysym.sym)
		{
		case SDLK_w:
			pikachu->setY(player->getY() - 10);// Move up
			break;
		case SDLK_s:
			pikachu->setY(player->getY() + 10); // Move down
			break;
		case SDLK_a:
			pikachu->setX(player->getX() - 10); // Move left
			break;
		case SDLK_d:
			pikachu->setX(player->getX() + 10); // Move right
			break;
		default:
			break;
		}*/
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

	if (player.getComponent<PositionComponent>().x() > 100)
	{
		player.getComponent<SpriteComponent>().setTex("assets/player.png");
	}

}
//---------------------------------------------------------------------------
void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);

}
//---------------------------------------------------------------------------
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}