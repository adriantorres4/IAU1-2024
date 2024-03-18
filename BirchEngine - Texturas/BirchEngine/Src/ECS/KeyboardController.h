#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
//#include "Nodo.h"
//#include "Grafo.h"
#include <thread>
#include <chrono>
#include "../AEstrella.h"
#include <fstream>
#include <string>
#include <sstream>

class KeyBoardController : public Component
{
public:
	int casillaNodoX;
	int casillaNodoY;
	int casillaValor;
	int posicionPersonajeX;
	int posicionPersonajeY;
	int difPosX;
	int difPosY;
	TransformComponent* transform;
	AEstrella::CoordinateList nodosColeccionables;
	KeyBoardController(AEstrella::CoordinateList camino, AEstrella::CoordinateList coleccionables) {
		this->caminoFinal = camino;
		this->nodosColeccionables = coleccionables;
	};
	KeyBoardController() = default;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

	}
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
	std::vector<std::vector<int>> leerArchivoMap(const std::string& nombreArchivo) {
		std::ifstream archivo(nombreArchivo); // Abrir el archivo en modo lectura
		std::vector<std::vector<int>> matriz;

		if (archivo.is_open()) { // Verificar si el archivo se abrió correctamente
			std::string linea;
			while (std::getline(archivo, linea)) { // Leer cada línea del archivo
				std::istringstream iss(linea);
				std::vector<int> fila;
				int numero;
				while (iss >> numero) { // Leer cada número de la línea
					fila.push_back(numero);
				}
				matriz.push_back(fila); // Agregar la fila a la matriz
			}
			archivo.close(); // Cerrar el archivo después de leerlo
		}
		else {
			std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
		}

		return matriz;
	}
	void pressKey(SDL_Keycode key) {
		SDL_Event event;
		event.type = SDL_KEYDOWN;
		event.key.keysym.sym = key;
		SDL_PushEvent(&event);

	}
	void update() override
	{

		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				if (!this->caminoFinal.empty()) {
					AEstrella::CoordinateList camino = this->caminoFinal;

					for (int i = camino.size() - 1;i > 0;i--) {
						casillaNodoX = camino.at(i).x;
						casillaNodoY = camino.at(i).y;
						//casillaValor = nodo->getValorCasilla();
						posicionPersonajeX = transform->position.x;
						posicionPersonajeY = transform->position.y;
						int casillaNodoSiguienteX = camino.at(i - 1).x;
						int casillaNodoSiguienteY = camino.at(i - 1).y;

						difPosX = casillaNodoSiguienteX * 64 - casillaNodoX * 64;
						difPosY = casillaNodoSiguienteY * 64 - casillaNodoY * 64;

						if (difPosX >= 0 && difPosY >= 0) {
							for (int i = 0; i < difPosX; i++)
							{

								//transform->position.x += 1;
								pressKey(SDLK_d);
								//std::this_thread::sleep_for(std::chrono::milliseconds(100));
							}
							for (int j = 0; j < difPosY;j++) {
								//transform->position.y += 1;
								pressKey(SDLK_s);
								//std::this_thread::sleep_for(std::chrono::milliseconds(100));
							}
						}
						if (difPosX < 0 && difPosY < 0) {
							for (int i = 0; i < (difPosX * -1); i++)
							{

								//transform->position.x -= 1;
								pressKey(SDLK_a);
								//std::this_thread::sleep_for(std::chrono::milliseconds(500));
							}
							for (int j = 0; j < (difPosY * -1);j++) {
								pressKey(SDLK_j);
								//transform->position.y -= 1;
								//std::this_thread::sleep_for(std::chrono::milliseconds(500));
							}
						}
						if (difPosX < 0 && difPosY >= 0) {
							for (int i = 0; i < (difPosX * -1); i++)
							{
								//transform->position.x -= 1;
								pressKey(SDLK_a);
								//std::this_thread::sleep_for(std::chrono::milliseconds(500));
							}
							for (int j = 0; j < difPosY;j++) {
								//transform->position.y += 1;
								pressKey(SDLK_s);
								//std::this_thread::sleep_for(std::chrono::milliseconds(500));
							}
						}
						if (difPosX >= 0 && difPosY < 0) {
							for (int i = 0; i < difPosX; i++)
							{
								pressKey(SDLK_d);
								//transform->position.x += 1;
								//std::this_thread::sleep_for(std::chrono::milliseconds(500));
							}
							for (int j = 0; j < (difPosY * -1);j++) {
								//transform->position.y -= 1;
								pressKey(SDLK_j);
								//std::this_thread::sleep_for(std::chrono::milliseconds(500));
							}
						}
						for (int i = 0;i < nodosColeccionables.size();i++) {
							vector<vector<int>>vectorMapa = leerArchivoMap("assets/map1.map");
							if (transform->position.x == nodosColeccionables.at(i).x && transform->position.y == nodosColeccionables.at(i).y) {
								
								int x = nodosColeccionables.at(i).x;
								int y = nodosColeccionables.at(i).y;
								x = x / 64;
								y = y / 64;
								vectorMapa[y][x] = 10;
								writeMapToFile(vectorMapa, "assets/map1.map");
								Map::LoadMap("assets/map1.map", 10, 10);
							}
						}



						/*if (posicionPersonajeX < casillaX) {
							while (posicionPersonajeX != casillaX) {
								transform->velocity.x = + 1;

							}
						}
						if (posicionPersonajeX > casillaX) {
							while (posicionPersonajeX != casillaX) {
								transform->velocity.x = -1;
							}
						}*/
					}

				}
				break;
			case SDLK_j:
				transform->position.y -= 1;
				break;
			case SDLK_a:
				transform->position.x -= 1;
				break;
			case SDLK_d:
				transform->position.x += 1;
				break;
			case SDLK_s:
				transform->position.y += 1;
				break;
			default:
				break;


			}
		}

		/*if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			default:
				break;


			}
		}*/

	}
private:
	AEstrella::CoordinateList caminoFinal;

};