#pragma once
#include <vector>
#include <istream>

#define blocksize 30
#define coinSize 6
#define ScoinSize 12
#define x_max 18
#define y_max 20


class EX_Map final : public std::exception
{
public:
	EX_Map() = delete;
	EX_Map(const char* what_) : std::exception(what_) {}
};

class Map
{
public:
	//загрузка карты из файла
	void LoadMap(const char* adress);
	//получить элемент матрицы [x;y]
	int& Get(int xdiv, int ydiv , int layer);
	//заменят все элементы del на add
	void Change(char del, char add , int layer);
	//очистить слой матрицу
	void ClearMap(int layer);
	//вывести матрицу
	void Print(int layer);
	//кол-во коинов
	int Coins();
	//обновление карты
	void Reset();
private:
	int map[y_max+1][x_max+1][4];
};

class Parser
{
public:
	void ParseLine(std::istream& stream);
	std::vector<char> Vector();
private:
	std::vector<char>vector = {};
};
