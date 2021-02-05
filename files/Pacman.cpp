#include "Pacman.hpp"
#include <iostream>

Game::Game() : graphic(19 * blocksize, 21 * blocksize), pacman('h'),
red('r'), pink('p'),blue('b'), yellow('y'),menu(graphic.GetRender()) , map()
{
	enemylist.push_back(yellow);
	enemylist.push_back(blue);
	enemylist.push_back(red);
	enemylist.push_back(pink);
};

bool Game::LoadTextures()
{
	try 
	{
		map.LoadMap("../Map/map.txt");
	}
	catch (EX_Map & ex)
	{
		std::cout << "Error: " << ex.what()<< std::endl;
		return false;
	}

	try
	{
		graphic.LoadTexture("coin", "../Textures/Blocks/coin.png");
		graphic.LoadTexture("emptyblock", "../Textures/Blocks/emptyblock.jpg");
		graphic.LoadTexture("wall", "../Textures/Blocks/wall.jpg");
		graphic.LoadTexture("blue", "../Textures/Enemy/blue.jpg");
		graphic.LoadTexture("pink", "../Textures/Enemy/pink.jpg");
		graphic.LoadTexture("yellow", "../Textures/Enemy/yellow.jpg");
		graphic.LoadTexture("red", "../Textures/Enemy/red.jpg");
		graphic.LoadTexture("pacman_close", "../Textures/Pacman/pacman1.png");
		graphic.LoadTexture("pacman_open", "../Textures/Pacman/pacman2.png");
		graphic.LoadTexture("pacman_close_kill", "../Textures/Pacman/pacman1angry.png");
		graphic.LoadTexture("pacman_open_kill", "../Textures/Pacman/pacman2angry.png");
		graphic.LoadTexture("reset", "../Textures/Enemy/reset.jpg");

		menu.LoadTexture("start_play", "../Textures/Menu/start_play.png");
		menu.LoadTexture("start_exit", "../Textures/Menu/start_exit.png");
		menu.LoadTexture("pause_exit", "../Textures/Menu/pause_exit.png");
		menu.LoadTexture("pause_continue", "../Textures/Menu/pause_continue.png");
		menu.LoadTexture("next_lvl", "../Textures/Menu/next_lvl.png");
		menu.LoadTexture("died_try", "../Textures/Menu/died_try.png");
		menu.LoadTexture("died_exit", "../Textures/Menu/died_exit.png");
		menu.LoadTexture("1", "../Textures/Menu/1.png");
		menu.LoadTexture("2", "../Textures/Menu/2.png");
		menu.LoadTexture("3", "../Textures/Menu/3.png");
		menu.LoadTexture("4", "../Textures/Menu/4.png");
		menu.LoadTexture("5", "../Textures/Menu/5.png");
	}
	catch (EX_Graphic& ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
		return false;
	}
}
void Game::Speed()
{
	float pacman_speed = 3;
	float enemy_speed = 1;

	switch (level)
	{
	case 1:
		pacman_speed = 3;
		enemy_speed = 1;
		break;
	case 2:
		pacman_speed = 3;
		enemy_speed = 1.5;
		break;
	case 3:
		pacman_speed = 3;
		enemy_speed = 2;
		break;
	case 4:
		pacman_speed = 3.5;
		enemy_speed = 2.5;
		break;
	case 5:
		pacman_speed = 4;
		enemy_speed = 3;
		break;
	}

	pacman.SetSpeed(pacman_speed) ;
	red.SetSpeed(enemy_speed) ;
	blue.SetSpeed(enemy_speed) ;
	pink.SetSpeed(enemy_speed) ;
	yellow.SetSpeed(enemy_speed);
}
void Game::LevelInitiazization()
{
	map.Reset();
	red.Activate();
	pink.NoActive();
	yellow.NoActive();
	blue.NoActive();
	pacman.Life();

	pacman.SetX(9 * blocksize);
	pacman.SetY(11 * blocksize);
	red.SetX(9 * blocksize);
	red.SetY(8 * blocksize);
	blue.SetX(8 * blocksize);
	blue.SetY(9 * blocksize);
	pink.SetX(9 * blocksize);
	pink.SetY(9 * blocksize);
	yellow.SetX(10 * blocksize);
	yellow.SetY(9 * blocksize);

	Speed();

	coins = map.Coins();
	allcoins = coins;
	time_animation = clock();
	timer = 0;
}
bool Game::KeybordOrganization(SDL_Event& event , const Uint8* nums)
{
	while (SDL_PollEvent(&event))
	{
		/*если нажатие кнопки*/
		if (event.type == SDL_KEYDOWN)
		{
			char expectation = 'a';
			/*данные о состоянии клавиатуры*/
			nums = SDL_GetKeyboardState(NULL);

			/*движ*/
			if (nums[SDL_SCANCODE_RIGHT] || nums[SDL_SCANCODE_D])
			{
				expectation = 'r';
			}
			else if (nums[SDL_SCANCODE_LEFT] || nums[SDL_SCANCODE_A])
			{
				expectation = 'l';
			}
			else if (nums[SDL_SCANCODE_DOWN] || nums[SDL_SCANCODE_S])
			{
				expectation = 'd';
			}
			else if (nums[SDL_SCANCODE_UP] || nums[SDL_SCANCODE_W])
			{
				expectation = 'u';
			}
			else if (nums[SDL_SCANCODE_ESCAPE])
			{
				if (!menu.PauseMenu(level))return false;
			}
			pacman.GetExpectation(expectation);
		}
	}
	return true;
}
void Game::EnemyAction()
{
	yellow.Motion(map, pacman, enemylist);
	yellow.AddonMap(map);

	pink.Motion(map, pacman, enemylist);
	pink.AddonMap(map);

	red.Motion(map, pacman, enemylist);
	red.AddonMap(map);

	blue.Motion(map, pacman, enemylist);
	blue.AddonMap(map);

}
void Game::PacmanAction()
{
	pacman.AddonMap(map);
	int motion = pacman.Motion(map);
	if (motion == 1)coins--;
	else if (motion == 2)
	{
		coins--;
		pacman.ModOn();
		timer = clock();
	}
}
void Game::ResultAction()
{
	if (pacman.Mod())
	{
		if (red.State() == 1)red.Run();
		if (yellow.State() == 1)yellow.Run();
		if (blue.State() == 1)blue.Run();
		if (pink.State() == 1)pink.Run();
	}

	if (pacman.Mod() && ((clock() - timer) / CLOCKS_PER_SEC > 5))
	{
		pacman.ModOff();

		if (red.State() == 2)red.Activate();
		if (yellow.State() == 2)yellow.Activate();
		if (blue.State() == 2)blue.Activate();
		if (pink.State() == 2)pink.Activate();

	}

	if ((coins <= (int)((float)allcoins * 0.8)) && (pink.State() == 0)) pink.Activate();
	if ((coins <= (int)((float)allcoins * 0.6)) && (blue.State() == 0)) blue.Activate();
	if ((coins <= (int)((float)allcoins * 0.4)) && (yellow.State() == 0)) yellow.Activate();
}
void Game::PrintGame()
{
	graphic.PrintMap(map);
	graphic.PrintEnemy(yellow);
	graphic.PrintEnemy(blue);
	graphic.PrintEnemy(pink);
	graphic.PrintEnemy(red);
	graphic.PrintPacman(pacman,time_animation);

	graphic.Present();
}
bool Game::ZeroCoin()
{
	bool exit = false;
	if (level < 5)level++;
	else exit = true;
	menu.WinMenu(level);
	graphic.Present();
	SDL_Delay(2500);

	if (exit)return false;
	return true;
}
void Game::Play()
{
	if (!LoadTextures())
	{
		system("pause");
		return;
	}

	if (!menu.StartMenu())return;
	level = 1;
	while (true)
	{
		LevelInitiazization();
		SDL_Event event;
		const Uint8* nums = NULL;
		while (true)
		{
			if(!KeybordOrganization(event, nums))return;
			EnemyAction();
			PacmanAction();
			ResultAction();
			PrintGame();
			if (coins == 0)
			{
				if (!ZeroCoin())return;
				break;
			}
			if (!pacman.State())
			{
				if (!menu.DiedMenu(level))return;
				else
				{
					level = 1;
					break;
				}
			}
		}
	}
}


