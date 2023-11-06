#include "SDLClass.h"


SDLClass::SDLClass()
{
	LoadMedia();
};

SDLClass::~SDLClass()
{
	Background.~TexClass();
	ClericSprite.~TexClass();
	FighterSprite.~TexClass();
	GoblinSprite.~TexClass();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	//	TTF_CloseFont(big_font);
	TTF_Quit();
	SDL_Quit();
};

void SDLClass::limitingFrames()
{
	int tmp = floor(framerate*240/60) -  (SDL_GetTicks() - start_tick);// 1000/60 wouldbe for 60frames per second  framerate was take from screen setting during Init() ethod
	if (tmp > 0)
	{
		SDL_Delay(tmp);
	}
	start_tick = SDL_GetTicks();
}

void SDLClass::Init()
{
	exitprogram = false;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cout<<"SDL could not initialize!"<< SDL_GetError()<<std::endl;
		return;
	}
	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cout << "Warning: Linear texture filtering not enabled!" << SDL_GetError() << std::endl;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "Fonts could not initialize!" << SDL_GetError() << std::endl;
		return;
	}
	SDL_DisplayMode dm;// screen info in display mode
	SDL_GetCurrentDisplayMode(0, &dm);
	framerate = dm.refresh_rate;
	screenWidth = ceil(dm.w * 0.7);
	minScreenWidth = ceil(dm.w * 0.3);
	screenHeight = ceil(dm.h * 0.7);
	minScreenHeight = ceil(dm.h * 0.6);

	//Create window\ SDL_WINDOW_RESIZABLE:
	gWindow = SDL_CreateWindow("Goblin dungeon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_RESIZABLE);
	if (gWindow == NULL)
	{
		std::cout << "Window could not be created!" << SDL_GetError() << std::endl;
		return;
	}
	//Create vsynced renderer for window
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL)
	{
		std::cout << "Renderer could not be created!" << SDL_GetError() << std::endl;
		return;
	}

	SDL_RenderClear(gRenderer);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not initialize!" << SDL_GetError() << std::endl;
	}
	else
	{
		this->LoadMedia();
	}


}

void SDLClass::LoadMedia()
{
	Background.loadFromFile("../Resources/room.png", gRenderer);
	ClericSprite.loadFromFile("../Resources/hat.png", gRenderer);
	FighterSprite.loadFromFile("../Resources/sword.png", gRenderer);
	GoblinSprite.loadFromFile("../Resources/goblin.png", gRenderer);

}

void SDLClass::CheckForEvents()
{

	while (SDL_PollEvent(&eventHandler) != 0)
	{
		checkForWindowEvent();
		checkForMouseEvent();
		checkForKeyboardEvent();
	}
} 

void SDLClass::checkForWindowEvent()
{
	if (eventHandler.type == SDL_WINDOWEVENT)
	{

		switch (eventHandler.window.event)
		{
		case SDL_WINDOWEVENT_MINIMIZED:
		{
			render = false;
			break;
		}
		case SDL_WINDOWEVENT_RESTORED:
		{
			render = true;
			break;
		}
		case SDL_WINDOWEVENT_RESIZED:
		{
			int widthTMP = screenWidth, heightTMP = screenHeight;

			int* width_handler, * height_handler; ;
			width_handler = &screenWidth;
			height_handler = &screenHeight;

			if (SDL_GetRendererOutputSize(gRenderer, width_handler, height_handler) != 0)
			{
				screenWidth = widthTMP;
				screenHeight = heightTMP;
				SDL_SetWindowSize(gWindow, screenWidth, screenHeight);
			}
			else
			{
				if (screenHeight < minScreenHeight)
				{
					screenHeight = minScreenHeight;
				}
				if (screenWidth < minScreenWidth)
				{
					screenWidth = minScreenWidth;
				}
				SDL_SetWindowSize(gWindow, screenWidth, screenHeight);

			}

			delete width_handler;
			delete height_handler;
			render = true;
			break;
		}
		case SDL_WINDOWEVENT_CLOSE:
			exitprogram = true;
			break;
		}
	}
}

void SDLClass::checkForMouseEvent()
{

	//SDL_GetMouseState(&x, &y);

	SDL_PumpEvents();
	switch (eventHandler.type)
	{
	case SDL_MOUSEMOTION:
	{
		break;
	}
	case SDL_MOUSEWHEEL:
	{
		//	eventHandler.wheel.y > 0
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{

		break;
	}
	default:
		break;
	}
	if (eventHandler.type == SDL_MOUSEMOTION)
	{
		render = true;
	}
	else if (eventHandler.type == SDL_MOUSEWHEEL)
	{
		render = true;
		//eventHandler.wheel.y > 0)
	
	}
}

void SDLClass::checkForKeyboardEvent()
{
	if (eventHandler.type == SDL_KEYDOWN)
	{
		switch (eventHandler.key.keysym.scancode)
		{

		case SDL_SCANCODE_ESCAPE:
		{
			exitprogram = true;

		}
		}
	}

}

