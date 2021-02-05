#include "Graphic.hpp"
#include <ctime>

Graphic::Graphic(size_t width, size_t height) : SDL2(width, height)
{
	textures.GetRender(GetRender());
};

void Graphic::PrintBlock(int xdiv, int ydiv, SDL_Texture* texture)
{
	Render(texture, xdiv * blocksize, ydiv * blocksize, blocksize);
}
void Graphic::PrintMap(Map& map)
{
	for (int y = 0; y < y_max+1; y++)
	{
		for (int x = 0; x < x_max+1; x++)
		{
			char type = map.Get(x, y, 0);

			if (type == 'x')
			{
				PrintBlock(x, y, textures["wall"]);
				continue;
			}

			PrintBlock(x, y, textures["emptyblock"]);

			if (type == 'c')
			{
				Render(textures["coin"], (x * blocksize) + blocksize / 2 - coinSize / 2, y * blocksize + blocksize / 2 - coinSize / 2, coinSize);
			}
			else if (type == 's')
			{
				Render(textures["coin"], x * blocksize + blocksize / 2 - ScoinSize / 2, y * blocksize + blocksize / 2 - ScoinSize / 2, ScoinSize);
			}
		}
	}
}
void Graphic::PrintEnemy(Enemy& enemy)
{
	SDL_Texture* texture = NULL;

	if (enemy.State() == 3)texture = textures["reset"];
	else
	{
		switch (enemy.GetID())
		{
		case 'r':
			texture = textures["red"];
			break;
		case 'p':
			texture = textures["pink"];
			break;
		case 'y':
			texture = textures["yellow"];
			break;
		case 'b':
			texture = textures["blue"];
			break;
		default:
			break;
		}
	}
	PrintUnit(enemy, texture);
}
void Graphic::PrintPacman(Pacman& pacman , int& time)
{
	int timer = (int)(pacman.GetSpeed() * 100);

	if (pacman.Mod())
	{
		if (clock() - time < timer)PrintUnit(pacman, textures["pacman_open_kill"]);
		else PrintUnit(pacman, textures["pacman_close_kill"]);
	}
	else
	{
		if (clock() - time < timer)PrintUnit(pacman, textures["pacman_open"]);
		else PrintUnit(pacman, textures["pacman_close"]);
	}

	if (clock() - time > timer*2)time = clock();
}
void Graphic::PrintUnit(Unit& unit, SDL_Texture* texture)
{
	Render(texture, (int)(unit.GetX()), (int)(unit.GetY()), blocksize);

	if (unit.GetX() < 0)
	{
		float x = unit.GetX();
		unit.SetX(x + (x_max + 1) * blocksize) ;
		Render(texture, (int)(unit.GetX()), (int)(unit.GetY()), blocksize);
		unit.SetX(x) ;
	}
	else if (unit.GetX() + blocksize - 1 > (x_max + 1)* blocksize)
	{
		float x = unit.GetX();
		unit.SetX(x - (x_max + 1) * blocksize) ;
		Render(texture, (int)(unit.GetX()), (int)(unit.GetY()), blocksize);
		unit.SetX(x);
	}

}
void Graphic::LoadTexture(std::string id_texture, const char* adress)
{
	textures.Load(id_texture, adress);
}
