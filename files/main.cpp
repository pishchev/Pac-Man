#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <ctime>

#include "Map.hpp"
#include "SDL2.hpp"
#include "Graphic.hpp"
#include "Menu.hpp"
#include "Pacman.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Game game;
	game.Play();

	return _CrtDumpMemoryLeaks();
}