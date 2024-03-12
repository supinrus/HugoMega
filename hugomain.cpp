#include <iostream>
#include <fstream>
#include "localfolder.hpp"
#include <SDL2/SDL.h>

typedef struct OPTHUGO
{
  Uint8 display;
  Uint8 numMiniGame;
} mainopt;
mainopt options;

#include "pixelset.hpp"

#include "formats/lzp.hpp"
#include "formats/wav.hpp"
#include "formats/raw.hpp"
#include "formats/pal.hpp"
#include "formats/til.hpp"
#include "formats/cgf.hpp"
#include "formats/font.hpp"
#include "formats/txt.hpp"
#include "formats/oos.hpp"

#include "intro/intro.hpp"
#include "menu/menu.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[])
{
	SDL_Window* window = NULL;
	options.display = 0;
	options.numMiniGame = 0;
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) !=0 )
	{
		return 1;
	}
	window = SDL_CreateWindow("Кузя. Мега-издание",SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	if (window==NULL)
	{
		SDL_Quit();
		return 1;
	}
	if (!playIntro(window))
	{
		if (playMenu(window))
		{
			SDL_DestroyWindow(window);
			SDL_Quit();
			return 1;
		}
	}
	else
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
