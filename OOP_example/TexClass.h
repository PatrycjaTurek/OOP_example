#pragma once
#include "pch.h"


class TexClass
{
private:

	void Free();

public:

	SDL_Texture* mTexture;

	int whichType;//to give different options to each

	void loadFromFile(std::string, SDL_Renderer*);	//Loads image from specified path
	void Render(SDL_Renderer*, SDL_Rect*);//on object SDL_rect
	void Render(SDL_Renderer*);//on whole window, almost only background

	TexClass();//Initializes variables
	~TexClass();//Deallocates memory	
};
