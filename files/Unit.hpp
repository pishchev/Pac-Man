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
	//�������� ����� ������ �� �����
	void AddonMap(Map& map);
	//�������� ID
	int GetID();

protected:
	//�������� ���������� ����������������� �������(���� �������� ���������)/true,���� ����������
	bool Centering(std::vector<int>& XY, float percent);
	//�������� 4 ���������� �������� ����� ������� 
	void GetSquare(int X, int Y, std::vector<std::vector<int>>& square);
	//�������� ����� �� ���������
	bool CanMove(std::vector<std::vector<int>>& square, Map& map);
	//������� ������ ���(��� �������� �� ����������� ������� �������� ����� CanMove)
	void FakeXY(int x, int y, char direction, std::vector<int>& vec);
	//������� ��� � �����������
	void Step(char direction);
	//���� ������� check ���� �� list - true
	bool CheckBlock(char check, std::vector<char> list);

	//��������� ����������� ��������
	char direction = 'a';
	int ID = 0;
	float x = 0;
	float y = 0;
	float speed = 0;

};

class Pacman final : public Unit
{
public:
	//�������� �������� �����������
	void GetExpectation(char expectation);
	Pacman(int ID, float x =0, float y =0, float speed =0) : Unit(ID, x, y, speed) {};
	//��������
	int Motion(Map& map);
	//���������
	bool Mod();
	//��������� ��������
	void ModOn();
	void ModOff();

	void Life();
	void Death();

	bool State();

private:
	//��������
	void Move(Map& map);
	//�������� �� ������ �������
	int GetCoin(Map& map);

	bool life = true;
	bool KillerMod = false;
	char expectation = 'a';
};

class Enemy : public Unit
{
public:
	Enemy(int ID, float x=0, float y=0, float speed=0) : Unit(ID, x, y, speed), xback(x), yback(y) {};
	//��������
	void Motion(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist);
	//���������
	int State();

	void Activate();
	void Run();
	void Reset();
	void NoActive();

protected:
	void virtual GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through) {};
	//������������ ���������� ��������
	void RandomDirection(Map& map, int x, int y);
	//�������� �������� ������; through - ����� ��� ����� ������
	void Search(Map& map, std::vector<char> through, int xstart, int ystart, int xfind, int yfind);
	//����� �����������
	void GetDirection(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist);
	//���� (���������� ��� �������)
	//������� ��������� ����������� � �����
	void BringDirection(Map& map, int xfind, int yfind);
	//����� �� �������
	void Run(Map& map, int xpac, int ypack);
	//�������� 
	void Move(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist);

private:

	float xback;
	float yback;
	/*
	0 - �� �����������
	1 - ����� �������
	2 - �����
	3 - ����������
	*/
	int state = 0;
};

class BlueGuy final : public Enemy
{
public:
	BlueGuy(int ID, float x=0, float y=0, float speed=0) : Enemy(ID, x, y, speed) {};
private:
	//�����������
	void GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through) override;
};
class PinkGuy final : public Enemy
{
public:
	PinkGuy(int ID, float x=0, float y=0, float speed=0) : Enemy(ID, x, y, speed) {};
private:
	//�����������
	void GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through)override;
};
class RedGuy final : public Enemy
{
public:
	RedGuy(int ID, float x=0, float y=0, float speed=0) : Enemy(ID, x, y, speed) {};
private:
	//�����������
	void GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through)override;
};
class YellowGuy final: public Enemy
{
public:
	YellowGuy(int ID, float x=0, float y=0, float speed=0) : Enemy(ID, x, y, speed) {};
private:
	//�����������
	void GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through)override;
};
