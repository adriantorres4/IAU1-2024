#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"


class TileComponent : public Component
{
	
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0: 
			path = "assets/water.png";
			break;
		case 1:
			path = "assets/dirt.png";
			break;
		case 2:
			path = "assets/grass.png";
			break;
		case 3:
			path = "assets/coleccionable1.png";
			break;
		case 4:
			path = "assets/coleccionable4.png";
			break;
		case 5:
			path = "assets/coleccionable5.png";
			break;
		case 6:
			path = "assets/snorlax-pasto.png";
			break;
		case 7:
			path = "assets/snorlax-dirt.png";
			break;
		case 8:
			path = "assets/arbol-pasto.png";
			break;
		case 9:
			path = "assets/arbol-dirt.png";
			break;
		case 10:
			path = "assets/coleccionable2.png";
			break;
		default:
			break;
		}
	}

	void init() override
	{
		entity->addComponent<TransformComponent>((float) tileRect.x, (float) tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};