#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <ctime>

#include "Map.hpp"
#include "SDL2.hpp"
#include "Graphic.hpp"
#include "Menu.hpp"

class Game
{
public:
	Game();
	void Play();
private:
	bool LoadTextures();
	void LevelInitiazization();
	bool KeybordOrganization(SDL_Event& event, const Uint8* nums);
	void EnemyAction();
	void PacmanAction();
	void ResultAction();
	void PrintGame();
	bool ZeroCoin();
	void Speed();

	Graphic graphic;
	Pacman pacman;
	RedGuy red;
	YellowGuy yellow;
	BlueGuy blue;
	PinkGuy pink;
	Menu menu;
	Map map;

	std::vector<Enemy> enemylist;

	
	int time_animation = 0;
	int level = 1;
	int timer = 0;
	int coins = 0;
	int allcoins = 0;

};