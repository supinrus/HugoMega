#include "step1.hpp"

Uint32 labyStart(Uint32 &score, Uint32 gameMode, Uint32 playerMode, SDL_Window *window, SDL_Surface *screen)
{
	Uint32 st = 1;
	rawFile introPic(getFullPath("LabyrinthData/gfx/INTROPIC.RAW"));
	cgfFile hugoSync(getFullPath("LabyrinthData/gfx/Hugosync.cgf"));
	wavFile introSpeak(getFullPath("LabyrinthData/Sfx/001-01.wav"));
	oosFile introSync(getFullPath("LabyrinthData/Sync/001-01.oos"));
	tilFile labyBack1(getFullPath("LabyrinthData/gfx/Baggrund_m.Sand4.til"));
	tilFile labyMap(getFullPath("LabyrinthData/gfx/ArcadeMap.til"));
	std::string pathMapArrows;
	if (!gameMode)
	{
		pathMapArrows = "LabyrinthData/gfx/MapArrows.cgf";
	}
	else
	{
		pathMapArrows = "LabyrinthData/gfx/ArcadeMapArrows.cgf";
	}
	cgfFile mapArrows(getFullPath(pathMapArrows));
	st = st*introPic.getStatus();
	st = st*hugoSync.getStatus();
	st = st*introSpeak.getStatus();
	st = st*introSync.getStatus();
	st = st*labyBack1.getStatus();
	st = st*labyMap.getStatus();
	st = st*mapArrows.getStatus();
	if (!st)
	{
		return 1;
	}
	introSync.playOos(introSpeak, hugoSync, -0x42, -0x10, introPic, window, screen);
	if (!labyStep1(score,gameMode,playerMode,window,screen,labyBack1,labyMap,mapArrows))
	{
	}
	return 0;
}
