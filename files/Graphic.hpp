#pragma once
#include "SDL2.hpp"
#include "Map.hpp"
#include "Unit.hpp"

class Graphic final : public SDL2
{
public:
	Graphic(size_t width, size_t height);
	//������� �������
	void PrintMap(Map& map);
	//�������� ����
	void PrintBlock(int xdiv, int ydiv, SDL_Texture* texture);
	//��������� ��������
	void PrintEnemy(Enemy& enemy);
	//��������� �������
	void PrintPacman(Pacman& pacman , int& time);
	//�������� ������
	void LoadTexture(std::string id_texture, const char* adress);

private:
	//���������� �����
	void PrintUnit(Unit& unit, SDL_Texture* texture);
	//��������
	Textures textures;

};