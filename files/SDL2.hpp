#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <exception>
#include <map>
#include <string>

class EX_Graphic final: public std::exception
{
public:
	EX_Graphic() = delete;
	EX_Graphic(const char* what_) : std::exception(what_) {}
};

class SDL2
{
public:
	SDL2(size_t width,size_t height);
	//add to render
	void Render(SDL_Texture* texture, int x, int y, int size);
	//show window
	void Present();
	virtual ~SDL2();
	//get render
	SDL_Renderer* GetRender();
private:
	SDL_Window* window;
	SDL_Renderer* render;
};

class Textures
{
public:
	Textures() = default;
	void GetRender(SDL_Renderer* _render);
	Textures(SDL_Renderer* render);
	SDL_Texture* operator[](std::string);
	void Load(std::string texture, const char* adress);
private:
	SDL_Renderer* render = NULL;
	std::map< std::string, SDL_Texture* > texture = {};
};
