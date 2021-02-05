#include "SDL2.hpp"
#include <fstream>

SDL2::SDL2(size_t width, size_t height)
{
	window = SDL_CreateWindow("Pacman", 100, 100, (int)width, (int)height, SDL_WINDOW_SHOWN);
	if (window == nullptr) throw EX_Graphic("Window is nulptr"); 
	
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (render == NULL)  throw EX_Graphic("Render is nulptr"); 
}
SDL2::~SDL2()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
}

void SDL2::Render(SDL_Texture* texture, int x, int y, int size)
{
	SDL_Rect rect;
	rect.h = size;
	rect.w = size;
	rect.x = x;
	rect.y = y;
	SDL_RenderCopy(render, texture, NULL, &rect);
}
void SDL2::Present()
{
	SDL_RenderPresent(render);
}
SDL_Renderer* SDL2::GetRender()
{
	return render;
}

Textures::Textures(SDL_Renderer* render) : render(render) {};
void Textures::Load(std::string id_texture, const char* adress)
{
	SDL_Texture* tex = IMG_LoadTexture(render, adress);
	if (!tex) throw EX_Graphic("texture is nullptr");
	texture.insert({ id_texture , tex });
}
SDL_Texture* Textures::operator[](std::string str)
{
	if (texture.find(str) == texture.end()) throw EX_Graphic("No texture");
	return texture[str];
}

void Textures::GetRender(SDL_Renderer* _render)
{
	render = _render;
}