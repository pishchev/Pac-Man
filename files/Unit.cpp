#include "Unit.hpp"
#include <map>
#include <vector>

float Unit::GetX()
{
	return (x);
}
float Unit::GetY()
{
	return y;
}
float Unit::GetSpeed()
{
	return speed;
}
char Unit::GetDirection()
{
	return direction;
}

void Unit::SetX(float _x)
{
	x =_x;
}
void Unit::SetY(float _y)
{
	y=_y;
}
void Unit::SetSpeed(float _speed)
{
	speed = _speed;
}
void Unit::SetDirection(char direct)
{
	direction = direct;
}

int Unit::GetID()
{
	return ID;
}
void Unit::AddonMap(Map& map)
{
	int x1 = (int)(x / blocksize);
	int y1 = (int)(y / blocksize);

	int x2 = (int)((x + blocksize - 1) / blocksize);
	int y2 = (int)((y + blocksize - 1) / blocksize);

	char el;

	if (ID == 'h')el = 'h';
	else if (ID == 'b')el = 'b';
	else if (ID == 'p')el = 'p';
	else if (ID == 'y')el = 'y';
	else if (ID == 'r')el = 'r';
	else return;

	map.Change(el, ' ', 1);

	map.Get(x1, y1, 1) = el;
	map.Get(x2, y2, 1) = el;

}
bool Unit::Centering(std::vector<int>& XY, float percent)
{
	int divX = XY[0] / blocksize;
	int divY = XY[1] / blocksize;
	int modX = XY[0] % blocksize;
	int modY = XY[1] % blocksize;

	int i = 0;

	if (modX > (int)(float(blocksize) - (float(blocksize) / 100 * percent)))
	{
		i++;
		divX++;
		if (divX == 19)divX = 0;
	}
	else if (modX < (int)(float(blocksize) / 100 * percent))
	{
		i++;
	}

	if (modY > (int)(float(blocksize) - (float(blocksize) / 100 * percent)))
	{
		i++;
		divY++;
	}
	else if (modY < (int)(float(blocksize) / 100 * percent))
	{
		i++;
	}

	if (i != 2) return false;

	XY.clear();
	XY.push_back(divX * blocksize);
	XY.push_back(divY * blocksize);

	return true;

}
void Unit::Step(char direction)
{
	switch (direction)
	{
	case 'u':
		y -= speed;
		break;
	case 'l':
		x -= speed;
		if (x + blocksize - 1 < 0) x = x_max * blocksize + (x + blocksize - 1);
		break;
	case 'r':
		x += speed;
		if (x > (x_max + 1)* blocksize) x -= (x_max + 1) * blocksize;
		break;
	case 'd':
		y += speed;
		break;
	}
}
void Unit::GetSquare(int X, int Y, std::vector<std::vector<int>>& square)
{
	std::vector<int> pair;

	int X1 = X;
	if (X1 < 0)X1 = (x_max + 1) * blocksize + X1;

	int X2 = X + blocksize - 1;
	if (X2 > (x_max + 1)* blocksize) X2 -= (x_max + 1) * blocksize;

	int Y1 = Y;
	int Y2 = Y + blocksize - 1;

	pair.push_back(X1); pair.push_back(Y1);
	square.push_back(pair);
	pair.clear();
	pair.push_back(X2); pair.push_back(Y1);
	square.push_back(pair);
	pair.clear();
	pair.push_back(X1); pair.push_back(Y2);
	square.push_back(pair);
	pair.clear();
	pair.push_back(X2); pair.push_back(Y2);
	square.push_back(pair);
}
bool Unit::CanMove(std::vector<std::vector<int>>& square, Map& map)
{
	int count = 0;
	for (auto it1 : square)
	{
		if (map.Get(it1[0] / blocksize, it1[1] / blocksize, 0) == 'x')count++;
	}
	return (count == 0);
}
void Unit::FakeXY(int _x, int _y, char direction, std::vector<int>& vec)
{
	switch (direction)
	{
	case 'u':
		_y -= (int)speed;
		break;
	case 'l':
		_x -= (int)speed;
		break;
	case 'r':
		_x += (int)speed;
		break;
	case 'd':
		_y += (int)speed;
		break;
	}

	vec.push_back(_x);
	vec.push_back(_y);
}
bool Unit::CheckBlock(char check, std::vector<char> list)
{
	for (auto it : list)
	{
		if (it == check)return true;
	}
	return false;
}

bool Pacman::Mod()
{
	return KillerMod;
}
int Pacman::Motion(Map& map)
{
	Move(map);
	return GetCoin(map);
}
void Pacman::Move(Map& map)
{
	std::vector<int> XY;
	XY.push_back((int)x); XY.push_back((int)y);

	if ((((expectation == 'r') || (expectation == 'l')) && ((direction == 'r') || (direction == 'l')))
		|| (((expectation == 'u') || (expectation == 'd')) && ((direction == 'u') || (direction == 'd'))))
	{
		direction = expectation;
	}
	else  if (Centering(XY, 10) && (expectation != 'a'))
	{
		std::vector<int> fakeXY_exp;
		FakeXY(XY[0], XY[1], expectation, fakeXY_exp);

		std::vector<std::vector<int>> square_exp;
		GetSquare(fakeXY_exp[0], fakeXY_exp[1], square_exp);

		if (CanMove(square_exp, map))
		{
			direction = expectation;
			expectation = 'a';
			x = (float)XY[0];
			y = (float)XY[1];
			return;
		}
	}
	// запилить в одну
	std::vector<int> fakeXY;
	FakeXY((int)x, (int)y, direction, fakeXY);

	std::vector<std::vector<int>> square;
	GetSquare(fakeXY[0], fakeXY[1], square);

	if (CanMove(square, map))
	{
		Step(direction);
		// фиксирует погрешность float
		std::vector<std::vector<int>> square;
		GetSquare((int)x, (int)y, square);
		if (CanMove(square, map))return;
	}
	{
		direction = 'a';
		std::vector<int> XY;
		XY.push_back((int)x); XY.push_back((int)y);
		Centering(XY, 10);
		x = (float)XY[0];
		y = (float)XY[1];
	}


}
void Pacman::GetExpectation(char _expectation)
{
	expectation = _expectation;
}
void Pacman::ModOn()
{
	KillerMod = true;
}
void Pacman::ModOff()
{
	KillerMod = false;
}
int Pacman::GetCoin(Map& map)
{
	int y_div_u =(int)( y / blocksize);
	int y_div_d = (int)((y + blocksize - 1) / blocksize);
	int y_mod = (int)y % blocksize;

	int x_div_l = (int)(x / blocksize);
	int x_div_r = (int)((x + blocksize - 1) / blocksize);
	int x_mod = (int)x % blocksize;

	if (map.Get(x_div_l, y_div_u, 0) == 'c')
	{
		if ((blocksize - x_mod + coinSize / 2 >= blocksize / 2) && (blocksize - y_mod + coinSize / 2 >= blocksize / 2))
		{
			map.Get(x_div_l, y_div_u, 0) = ' ';
			return 1;
		}
	}
	else if(map.Get(x_div_l, y_div_u, 0) == 's')
	{
		if ((blocksize - x_mod + ScoinSize / 2 >= blocksize / 2) && (blocksize - y_mod + ScoinSize / 2 >= blocksize / 2))
		{
			map.Get(x_div_l, y_div_u, 0) = ' ';
			return 2;
		}
	}

	if (map.Get(x_div_r, y_div_d, 0) == 'c')
	{
		if ((x_mod + coinSize / 2 >= blocksize / 2) || (y_mod + coinSize / 2 >= blocksize / 2))
		{
			map.Get(x_div_r, y_div_d, 0) = ' ';
			return 1;
		}
	}
	else if (map.Get(x_div_r, y_div_d, 0) == 's')
	{
		if ((x_mod + ScoinSize / 2 >= blocksize / 2) || (y_mod + ScoinSize / 2 >= blocksize / 2))
		{
			map.Get(x_div_r, y_div_d, 0) = ' ';
			return 2;
		}
	}

	return 0;

}
void Pacman::Life()
{
	life = true;
}
void Pacman::Death()
{
	life = false;
}
bool Pacman::State()
{
	return life;
}

int Enemy::State()
{
	return state;
}
void Enemy::Search(Map& map, std::vector<char> through, int xstart, int ystart, int xfind, int yfind)
{
	bool stop = false;

	std::vector<int> start;
	start.push_back(xstart);
	start.push_back(ystart);
	start.push_back(1);

	std::vector<std::vector<int>> wave;
	wave.push_back(start);

	while (!stop)
	{
		if (wave.empty())return;

		int _x = wave[0][0];
		int _y = wave[0][1];
		int count = wave[0][2];

		if (xfind == _x && yfind == _y)
		{
			stop = true;
		}
		else if ((map.Get(_x, _y, 0) != 'x') && CheckBlock(map.Get(_x, _y, 1), through))
		{
			if (map.Get(_x, _y, 2) == 0)map.Get(_x, _y, 2) = count;
			else if (map.Get(_x, _y, 2) > count)map.Get(_x, _y, 2) = count;
			else
			{
				wave.erase(wave.begin());
				continue;
			}
		}
		else
		{
			wave.erase(wave.begin());
			continue;
		}

		wave.erase(wave.begin());

		std::vector<int> up;
		up.push_back(_x); up.push_back(_y - 1); up.push_back(count + 1);
		wave.push_back(up);

		std::vector<int> right;
		if (_x + 1 > x_max)	right.push_back(0);
		else right.push_back(_x + 1);

		right.push_back(_y); right.push_back(count + 1);
		wave.push_back(right);

		std::vector<int> down;
		down.push_back(_x); down.push_back(_y + 1); down.push_back(count + 1);
		wave.push_back(down);

		std::vector<int> left;
		if (_x - 1 < 0)left.push_back(x_max);
		else left.push_back(_x - 1);

		left.push_back(_y); left.push_back(count + 1);
		wave.push_back(left);
	}

}
void Enemy::RandomDirection(Map& map, int _x, int _y)
{
	char free[] = { 0,0,0,0 };
	// дописать или пакмен
	if ((map.Get(_x, _y - 1, 1) == ' ' || (map.Get(_x, _y - 1, 1) == 'h') && map.Get(_x, _y - 1, 0) != 'x'))free[0] = 1;
	if ((map.Get(_x + 1, _y, 1) == ' ' || (map.Get(_x + 1, _y, 1) == 'h') && map.Get(_x + 1, _y, 0) != 'x')) free[1] = 1;
	if ((map.Get(_x, _y + 1, 1) == ' ' || (map.Get(_x, _y + 1, 1) == 'h') && map.Get(_x, _y + 1, 0) != 'x')) free[2] = 1;
	if ((map.Get(_x - 1, _y, 1) == ' ' || (map.Get(_x - 1, _y, 1) == 'h') && map.Get(_x - 1, _y, 0) != 'x')) free[3] = 1;

	int result = rand() % 4;

	int random = -1;

	for (int i = 0; i < 4; i++)
	{
		if (result == 4)result = 0;
		if (free[result] == 1)random = result;
	}

	if (random != -1)
	{
		switch (random)
		{
		case 0:
			direction = 'u';
			break;
		case 1:
			direction = 'r';
			break;
		case 2:
			direction = 'd';
			break;
		case 3:
			direction = 'l';
			break;
		}
	}
}
void Enemy::BringDirection(Map& map, int xfind, int yfind)
{
	int min = INT_MAX;
	if (map.Get(xfind, yfind - 1, 2) < min && map.Get(xfind, yfind - 1, 2) != 0)
	{
		min = map.Get(xfind, yfind - 1, 2);
		direction = 'u';
	}
	if (map.Get(xfind + 1, yfind, 2) < min && map.Get(xfind + 1, yfind, 2) != 0)
	{
		min = map.Get(xfind + 1, yfind, 0);
		direction = 'r';
	}
	if (map.Get(xfind, yfind + 1, 2) < min && map.Get(xfind, yfind + 1, 2) != 0)
	{
		min = map.Get(xfind + 1, yfind, 2);
		direction = 'd';
	}
	if (map.Get(xfind - 1, yfind, 2) < min && map.Get(xfind - 1, yfind, 2) != 0)
	{
		min = map.Get(xfind + 1, yfind, 2);
		direction = 'l';
	}
}
void Enemy::Run(Map& map, int xpac, int ypack)
{
	int _x = (int)(x / blocksize);
	int _y = (int)(y / blocksize);

	int vector_y = ypack - _y;
	int vector_x = xpac - _x;

	std::multimap<int, char>direct;

	direct.insert({ -vector_y, 'u' });
	direct.insert({ vector_y, 'd' });
	direct.insert({ vector_x, 'r' });
	direct.insert({ -vector_x, 'l' });


	for (int i = 0; i < 4; i++)
	{
		char dir = direct.begin()->second;

		switch (dir)
		{
		case 'u':
			if ((map.Get(_x, _y - 1, 0) != 'x') && (map.Get(_x, _y - 1, 1) == ' '))
			{
				direction = 'u';
				return;
			}
			break;
		case 'r':
			if ((map.Get(_x + 1, _y, 0) != 'x') && (map.Get(_x + 1, _y, 1) == ' '))
			{
				direction = 'r';
				return;
			}
			break;
		case 'd':
			if ((map.Get(_x, _y + 1, 0) != 'x') && (map.Get(_x, _y + 1, 1) == ' '))
			{
				direction = 'd';
				return;
			}
			break;
		case 'l':
			if ((map.Get(_x - 1, _y, 0) != 'x') && (map.Get(_x - 1, _y, 1) == ' '))
			{
				direction = 'l';
				return;
			}
			break;
		}
		direct.erase(direct.begin());
	}


}
void Enemy::GetDirection(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist)
{
	std::vector<int> coordinate;
	coordinate.resize(4);
	std::vector<char> through;
	through.push_back(' ');
	through.push_back('h');

	coordinate[2] = (int)(x / blocksize);
	coordinate[3] = (int)(y / blocksize);

	if (state == 1)
	{
		GetTarget(map, pacman, enemylist, coordinate, through);
	}
	else if (state == 3)
	{
		coordinate[1] = 9;
		coordinate[0] = 9;
	}
	else if (state == 2)
	{
		coordinate[1] = (int)(pacman.GetX() / blocksize);
		coordinate[0] = (int)(pacman.GetY() / blocksize);
	}

	int xstart = coordinate[0];
	int ystart = coordinate[1];

	int xfind = coordinate[2];
	int yfind = coordinate[3];
	bool stop = false;

	Search(map, through, xstart, ystart, xfind, yfind);

	direction = 'a';

	if (state == 2)
	{
		Run(map, (int)(pacman.GetX() / blocksize), (int)(pacman.GetY() / blocksize));
	}

	if (state == 1 || state == 3)
	{
		BringDirection(map, xfind, yfind);
	}

	if (direction == 'a')
	{
		RandomDirection(map, xfind, yfind);
	}
	map.ClearMap(2);
}
void Enemy::Move(Map& map, Pacman& find, std::vector<Enemy>& enemylist)
{
	std::vector<int> XY;
	XY.push_back((int)x); XY.push_back((int)y);

	if (direction == 'a')GetDirection(map, find, enemylist);

	if (Centering(XY, 10) && ((XY[0] != xback) || (XY[1] != yback)))
	{
		x = (float)XY[0];
		y = (float)XY[1];

		GetDirection(map, find, enemylist);

		xback = (float)XY[0];
		yback = (float)XY[1];
	}

	// запилить в одну
	std::vector<int> fakeXY;
	FakeXY((int)x, (int)y, direction, fakeXY);

	std::vector<std::vector<int>> square;
	GetSquare(fakeXY[0], fakeXY[1], square);

	if (CanMove(square, map))
	{
		Step(direction);

		// фиксирует погрешность float
		std::vector<std::vector<int>> square;
		GetSquare((int)x, (int)y, square);
		if (CanMove(square, map))return;
	}
	{
		std::vector<int> XY;
		XY.push_back((int)x); XY.push_back((int)y);
		Centering(XY, 10);
		x = (float)XY[0];
		y = (float)XY[1];

		xback = (float)XY[0];
		yback = (float)XY[1];

		GetDirection(map, find, enemylist);
	}
}
void Enemy::Motion(Map& map, Pacman& find, std::vector<Enemy>& enemylist)
{
	if (state == 0)return;

	Move(map, find, enemylist);

	if (state == 1)
	{
		int x1 = (int)x;
		int x2 = (int)(x + blocksize - 1);
		int y1 = (int)y;
		int y2 = (int)(y + blocksize - 1);

		std::vector < std::vector<int>> vector;
		GetSquare((int)(find.GetX()), (int)(find.GetY()), vector);

		for (auto it : vector)
		{
			int xp = it[0];
			int yp = it[1];

			if ((xp >= x1 && xp <= x2) && (yp >= y1 && yp <= y2))
			{
				find.Death();
			}

		}
	}
	if (state == 3)
	{
	
		int x1 = (int)(x/blocksize);
		int y1 = (int)(y/blocksize);
		
		if (x1 == 9 && y1 == 9)
		{
			Activate();
		}

	}
	if (state == 2)
	{
		
		int x1 = (int)x;
		int x2 = (int)(x + blocksize - 1);
		int y1 = (int)y;
		int y2 = (int)(y + blocksize - 1);

		std::vector < std::vector<int>> vector;
		GetSquare((int)(find.GetX()), (int)(find.GetY()), vector);

		for (auto it : vector)
		{
			int xp = it[0];
			int yp = it[1];

			if ((xp >= x1 && xp <= x2) && (yp >= y1 && yp <= y2))
			{
				Reset();
			}

		}

	}
}
void Enemy::Activate()
{
	state = 1;
}
void Enemy::Run()
{
	state = 2;
}
void Enemy::Reset()
{
	state = 3;
}
void Enemy::NoActive()
{
	state = 0;
}

void RedGuy::GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through)
{
	coordinate[0] = (int)(pacman.GetX() / blocksize);
	coordinate[1] = (int)(pacman.GetY() / blocksize);

	through.push_back('r');
}
void BlueGuy::GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through)
{
	through.push_back('b');

	coordinate[0] = (int)(pacman.GetX() / blocksize);
	coordinate[1] = (int)(pacman.GetY() / blocksize);

	int red_x = -1;
	int red_y = -1;

	for (auto it = enemylist.begin(); it != enemylist.end(); it++)
	{
		if (it->GetID() == 'r')
		{
			red_x = (int)(it->GetX() / blocksize);
			red_y = (int)(it->GetY() / blocksize);
			break;
		}
	}

	if (red_x == -1 || red_y == -1)return;

	int pac_x = (int)(pacman.GetX() / blocksize);
	int pac_y = (int)(pacman.GetY() / blocksize);

	int vector_x = pac_x - red_x;
	int vector_y = pac_y - red_y;

	while (vector_x != 0 || vector_y != 0)
	{
		if (pac_x + vector_x >= 0 && pac_y + vector_y >= 0 && pac_x + vector_x <= x_max && pac_y + vector_y <= y_max)
		{
			if (map.Get(pac_x + vector_x, pac_y + vector_y, 0) != 'x' && map.Get(pac_x + vector_x, pac_y + vector_y, 1) == ' ')
			{
				break;
			}
		}

		if (vector_x > 0)vector_x--;
		else if (vector_x < 0)vector_x++;

		if (vector_y > 0)vector_y--;
		else if (vector_y < 0)vector_y++;
	}

	coordinate[0] = pac_x + vector_x;
	coordinate[1] = pac_y + vector_y;

}
void PinkGuy::GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through)
{
	coordinate[0] = (int)(pacman.GetX() / blocksize);
	coordinate[1] = (int)(pacman.GetY() / blocksize);

	int _x = coordinate[0];
	int _y = coordinate[1];

	through.push_back('p');

	int i = 4;

	while (i > 0)
	{
		int new_x = _x;
		int new_y = _y;
		switch (pacman.GetDirection())
		{
		case 'u':
			new_y -= i;
			break;
		case 'r':
			new_x += i;
			break;
		case 'd':
			new_y += i;
			break;
		case 'l':
			new_x -= i;
			break;
		}

		if ((map.Get(new_x, new_y, 0) != 'x') && (map.Get(new_x, new_y, 1) == ' '))
		{
			coordinate[0] = new_x;
			coordinate[1] = new_y;
			return;
		}

		i--;
	}

}
void YellowGuy::GetTarget(Map& map, Pacman& pacman, std::vector<Enemy>& enemylist, std::vector<int>& coordinate, std::vector<char>& through)
{
	coordinate[0] = (int)(pacman.GetX() / blocksize);
	coordinate[1] = (int)(pacman.GetY() / blocksize);

	int yel_x = (int)(x / blocksize);
	int yel_y = (int)(y / blocksize);

	if (abs(yel_x - coordinate[0]) < 6 && abs(yel_y - coordinate[1]) < 6)
	{
		coordinate[0] = 0;
		coordinate[1] = 0;
	}


	through.push_back('r');
}