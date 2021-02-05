#pragma once
#include "Map.hpp"
#include <map>

class Unit
{
public:
	Unit(int ID, float x = 0, float y = 0, float speed = 0) : ID(ID), x(x), y(y), speed(speed) {};

	float GetSpeed();
	char GetDirection();
	float GetX();
	float GetY();

	void SetX(float _x);
	void SetY(float _y);
	void SetSpeed(float _speed);
	void SetDirection(char direct);

	virtual ~Unit() = default;
	//добавить метки юнитов на карту
	void AddonMap(Map& map);
	//получить ID
	int GetID();

protected:
	//получить координаты отцентрированного объекта(если точность позволяет)/true,если получилось
	bool Centering(std::vector<int>& XY, float percent);
	//получить 4 координаты ключевых точек объекта 
	void GetSquare(int X, int Y, std::vector<std::vector<int>>& square);
	//проверка может ли двигаться
	bool CanMove(std::vector<std::vector<int>>& square, Map& map);
	//сделать мнимый шаг(для проверки на возможность данного действия через CanMove)
	void FakeXY(int x, int y, char direction, std::vector<int>& vec);
	//сделать шаг в направлении
	void Step(char direction);
	//если элемент check один из list - true
	bool CheckBlock(char check, std::vector<char> list);

	//начальное направление движения
	char direction = 'a';
	int ID = 0;
	float x = 0;
	float y = 0;
	float speed = 0;

};

class Pacman final : public Unit
{
public:
	//изменить ожидание направления
	void GetExpectation(char expectation);
	Pacman(int ID, float x =0, float y =0, float speed =0) : Unit(ID, x, y, speed) {};
	//движение
	int Motion(Map& map);
	//состояние
	bool Mod();
	//активация агрессии
	void ModOn();
	void ModOff();

	void Life();
	void Death();

	bool State();

private:
	//движение
	void Move(Map& map);
	//проверка на взятие монетки
	int GetCoin(Map& map);

	bool life = true;
	bool KillerMod = false;
	char expectation = 'a';
};

class Enemy : public Unit
{
public:
	Enemy(int ID, float x=0, float y=0, float speed=0) : Unit(ID, x, y, speed), xback(x), yback(y) {};
	//движение
	void Motion(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist);
	//состояние
	int State();

	void Activate();
	void Run();
	void Reset();
	void NoActive();

protected:
	void virtual GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through) {};
	//произвольное допустимое движение
	void RandomDirection(Map& map, int x, int y);
	//волновой алгоритм поиска; through - через что можно пройти
	void Search(Map& map, std::vector<char> through, int xstart, int ystart, int xfind, int yfind);
	//новое направление
	void GetDirection(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist);
	//цель (специфична для каждого)
	//выбрать ближайшее направление к точке
	void BringDirection(Map& map, int xfind, int yfind);
	//побег от пакмена
	void Run(Map& map, int xpac, int ypack);
	//движение 
	void Move(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist);

private:

	float xback;
	float yback;
	/*
	0 - не активирован
	1 - поиск пакмена
	2 - побег
	3 - обновление
	*/
	int state = 0;
};

class BlueGuy final : public Enemy
{
public:
	BlueGuy(int ID, float x=0, float y=0, float speed=0) : Enemy(ID, x, y, speed) {};
private:
	//направление
	void GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through) override;
};
class PinkGuy final : public Enemy
{
public:
	PinkGuy(int ID, float x=0, float y=0, float speed=0) : Enemy(ID, x, y, speed) {};
private:
	//направление
	void GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through)override;
};
class RedGuy final : public Enemy
{
public:
	RedGuy(int ID, float x=0, float y=0, float speed=0) : Enemy(ID, x, y, speed) {};
private:
	//направление
	void GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through)override;
};
class YellowGuy final: public Enemy
{
public:
	YellowGuy(int ID, float x=0, float y=0, float speed=0) : Enemy(ID, x, y, speed) {};
private:
	//направление
	void GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through)override;
};
