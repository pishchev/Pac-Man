#include "Menu.hpp"

void Menu::LoadTexture(std::string id_texture, const char* adress)
{
	textures.Load(id_texture, adress);
}
void Menu::BackGround(SDL_Texture* texture)
{
	SDL_Rect rect;
	rect.h = (y_max + 1) * blocksize;
	rect.w = (x_max + 1) * blocksize;
	rect.x = 0;
	rect.y = 0;
	SDL_RenderCopy(render, texture, NULL, &rect);
}
int Menu::Chose(SDL_Texture* text1, SDL_Texture* text2, int lvl)
{
	int state = 1;
	BackGround(text1);
	if (lvl != 0)PrintMenuLvl(lvl);
	SDL_Event event;
	const Uint8* nums = NULL;
	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				nums = SDL_GetKeyboardState(NULL);

				if (nums[SDL_SCANCODE_DOWN])
				{
					state = 2;
					BackGround(text2);
				}
				else if (nums[SDL_SCANCODE_UP])
				{
					state = 1;
					BackGround(text1);
				}

				if (lvl != 0)PrintMenuLvl(lvl);

				if (nums[SDL_SCANCODE_RETURN])
				{
					return state;
				}
			}
		}
		SDL_RenderPresent(render);
	}
}
bool Menu::StartMenu()
{
	return  (Chose(textures["start_play"], textures["start_exit"]) == 1);
}
bool Menu::PauseMenu(int lvl)
{
	return  (Chose(textures["pause_continue"], textures["pause_exit"], lvl) == 1);
}
bool Menu::DiedMenu(int lvl)
{
	return  (Chose(textures["died_try"], textures["died_exit"], lvl) == 1);
}
void Menu::PrintMenuLvl(int lvl)
{
	std::string num_lvl;
	switch (lvl)
	{
	case 1:
		num_lvl = "1";
		break;
	case 2:
		num_lvl = "2";
		break;
	case 3:
		num_lvl = "3";
		break;
	case 4:
		num_lvl = "4";
		break;
	case 5:
		num_lvl = "5";
		break;
	}

	SDL_Rect rect;
	rect.h = 2 * blocksize;
	rect.w = 2 * blocksize;
	rect.x = 290;
	rect.y = 40;
	SDL_RenderCopy(render, textures[num_lvl], NULL, &rect);

}
void Menu::WinMenu(int lvl)
{
	BackGround(textures["next_lvl"]);
	PrintMenuLvl(lvl);
}

Menu::Menu(SDL_Renderer* render):render(render)
{
	textures.GetRender(render);
	
}