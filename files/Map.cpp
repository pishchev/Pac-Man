#include "Map.hpp"
#include <vector>
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

void Map::LoadMap(const char* adress)
{
	std::fstream stream;
	stream.open(adress);
	if (!stream) throw EX_Map("File is nullptr");
	int lines = 0;
	while (!stream.eof())
	{
		Parser line;
		line.ParseLine(stream);
		std::vector<char> vec;
		vec = line.Vector();

		if (vec.size() != 19) throw EX_Map("Incorrect map");

		for (int i = 0; i < x_max+1; i++)
		{
			map[lines][i][0] = vec[i];
			map[lines][i][3] = vec[i];
		}
		lines++;
	}
	if (lines != y_max + 1) throw EX_Map("Incorrect map");

	ClearMap(1);
	Change(0, ' ', 1);
	ClearMap(2);
}
int& Map::Get(int xdiv, int ydiv,int layer)
{
	if (xdiv < 0)return map[ydiv][ x_max][layer];
	if (xdiv > x_max)return map[ydiv][0][layer];
	return map[ydiv][xdiv][layer];
}
void Map::ClearMap(int layer)
{
	for (int i = 0; i < y_max + 1; i++)
	{
		for (int k = 0; k < x_max + 1; k++)
		{
			map[i][k][layer] = 0;
		}
	}
}
void Map::Change(char del , char add ,int layer)
{
	for (int i = 0; i < y_max + 1; i++)
	{
		for (int k = 0; k < x_max + 1; k++)
		{
			if (map[i][k][layer] == del)map[i][k][layer] = add;
		}
	}
}
void Map::Print(int layer)
{
	system("cls");

	for (int i = 0; i < y_max + 1; i++)
	{
		for (int k = 0; k < x_max + 1; k++)
		{
			std::cout << map[i][k][layer];
		}
		std::cout << std::endl;
	}
}
int Map::Coins()
{
	int count = 0;
	for (int i = 0; i < y_max + 1; i++)
	{
		for (int k = 0; k < x_max + 1; k++)
		{
			if (map[i][k][0] == 'c' || map[i][k][0] == 's')count++;
		}
	}
	return count;
}
void Map::Reset()
{
	for (int i = 0; i < y_max + 1; i++)
	{
		for (int k = 0; k < x_max + 1; k++)
		{
			map[i][k][0] = map[i][k][3];
		}
	}
}

std::vector<char> Parser::Vector()
{
	return vector;
}
void Parser::ParseLine(std::istream& stream)
{
	std::string line;
	std::getline(stream, line);
	for (int i = 0; i < line.size(); i++)
	{
		vector.push_back(line[i]);
	}
}
