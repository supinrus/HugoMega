void labyMapLoad(SDL_Surface *screen, tilFile &labyMap, cgfFile &mapArrows, Uint32 mapX0, Uint32 mapY0,
				Uint32 mapX, Uint32 mapY, Uint32 gameMode, Uint32 numArrow)
{
	labyMap.loadFrame(gameMode,screen);
	mapArrows.draw(numArrow%4,(mapX-mapX0)*5,(mapY-mapY0)*5,1,screen,1,0);
}

Uint32 labyStep1(Uint32 &score, Uint32 gameMode, Uint32 playerMode, SDL_Window *window, SDL_Surface *screen,
				tilFile& labyBack1, tilFile &labyMap, cgfFile &mapArrows)
{
	SDL_Event e;
	Uint32 mapX0, mapY0;
	if (!gameMode)
	{
		mapX0 = 0x13;
		mapY0 = 0x23;
	}
	else
	{
		mapX0 = 0x17;
		mapY0 = 0x2A;
	}
	Uint32 mapX = mapX0, mapY = mapY0;
	labyMapLoad(screen,labyMap,mapArrows,mapX0,mapY0,mapX,mapY,gameMode,0);
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);
	return 0;
}
