#pragma once
#include "SDL2.hpp"
#include "Map.hpp"
#include "Unit.hpp"

class Graphic final : public SDL2
{
public:
	Graphic(size_t width, size_t height);
	//вывести матрицу
	void PrintMap(Map& map);
	//добавить блок
	void PrintBlock(int xdiv, int ydiv, SDL_Texture* texture);
	//отрисовка призрака
	void PrintEnemy(Enemy& enemy);
	//отрисовка пакмена
	void PrintPacman(Pacman& pacman , int& time);
	//загрузка тестур
	void LoadTexture(std::string id_texture, const char* adress);

private:
	//нарисовать юнита
	void PrintUnit(Unit& unit, SDL_Texture* texture);
	//текстуры
	Textures textures;

};