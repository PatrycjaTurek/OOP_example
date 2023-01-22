
#pragma once
#include "pch.h"
#include "TexClass.h"

class SDLClass
{
	protected:
		TexClass Background;
		TexClass ClericSprite;
		TexClass FighterSprite;
		TexClass GoblinSprite;

		void LoadMedia();

		void MainMenuDisplay();//main menu
		void Free();

		SDL_Event eventHandler;		//SDL_Event handler
		SDL_Window* gWindow; //main window
		SDL_Renderer* gRenderer;//main renderer

		Uint32 start_tick;

		int framerate;
		int font_size;

		int screenWidth, minScreenWidth;
		int screenHeight, minScreenHeight;

		bool render;//true if something have changed since last Render

		void Init();
		void CheckForEvents();
		void checkForWindowEvent();
		void checkForMouseEvent();
		void checkForKeyboardEvent();
		void checkForKeyboardEvent_NoteScreen();

		void limitingFrames();

	public:

		bool exitprogram; // if terminate program 
		SDLClass();
		~SDLClass();
	};


