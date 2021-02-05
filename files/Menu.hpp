#pragma once
#include "SDL2.hpp"
#include "Map.hpp"

class Menu
{
public:
	Menu(SDL_Renderer * render);
	void BackGround(SDL_Texture* texture);
	void LoadTexture(std::string id_texture, const char* adress);
	bool StartMenu();
	bool PauseMenu(int lvl);
	bool DiedMenu(int lvl);
	void WinMenu(int lvl);
	void PrintMenuLvl(int lvl);
private:
	int Chose(SDL_Texture* text1, SDL_Texture* text2, int lvl = 0);
	Textures textures;
	SDL_Renderer* render = NULL;
};
