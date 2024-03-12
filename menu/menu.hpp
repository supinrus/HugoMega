#include "options.hpp"
#include "hiscore.hpp"
#include "../games/laby/start.hpp"

void hideFilm(SDL_Surface *screen, SDL_Surface *bkgr, SDL_Window *window,
				Uint32 tintLeft, Uint32 tintRight, Uint32 tintUp, Uint32 tintDown,
				Uint32 &filmX, Uint32 &filmY, cgfFile &arrows, cgfFile &film,
				wavFile *filmStart, wavFile &filmStop, rawFile *gamePics, cgfFile &modeIcons,
				Uint32 gameMode, cgfFile &playerIcons, Uint32 playerMode,
				fontText &ultraFont, textFile &gameNames, fontText &menuFont,
				textFile &menuText, wavFile &music, Uint32 &timeMusic)
{
	Uint8 numSound = 0;
	filmStart[0].clearAudio();
	filmStart[1].clearAudio();
	filmStart[numSound].loadAudio();
	filmStart[numSound].playAudio();
	Uint32 timeAudio = SDL_GetTicks();
	while (filmY!=0x1F6)
	{
		Uint32 timer = SDL_GetTicks();
		filmY += 0x10;
		SDL_BlitSurface(bkgr,NULL,screen,NULL);
		arrows.draw(0,0x102,0x140,0,screen,tintDown,0);
		arrows.draw(2,0x102,0x140,0,screen,tintLeft,0);
		arrows.draw(4,0x102,0x140,0,screen,tintRight,0);
		arrows.draw(6,0x102,0x140,0,screen,tintUp,0);
		for (Uint32 i = 0; i<21; ++i)
		{
			if ((filmY+i*0x80<480)||(filmY+(i+1)*0x80<480))
			{
				gamePics[i].draw(0x1BA,filmY+i*0x80+4,0,0,0,screen,4);
				ultraFont.printText(gameNames[i],0x1BA,filmY+i*0x80+4,screen,4,0);
				film.draw(0,filmX,filmY+i*0x80,0,screen,1,0);
			}
		}
		for (Uint32 i = 0; i<5; ++i)
		{
			menuFont.printText(menuText[i],0x14,0xA8+i*0x2A,screen,1,1);
		}
		modeIcons.draw(gameMode,0x16C,0xAC,0,screen,1,0);
		playerIcons.draw(playerMode,0x16C,0xD9,0,screen,1,0);
		SDL_UpdateWindowSurface(window);
		while(SDL_GetTicks()-timer<30)
		{
			if (SDL_GetTicks()-timeAudio>=filmStart[numSound].getTimeLength()-2050)
			{
				numSound = (numSound+1)%2;
				filmStart[numSound].clearAudio();
				filmStart[numSound].loadAudio();
				filmStart[numSound].playAudio();
				timeAudio = SDL_GetTicks();
			}
			if (SDL_GetTicks()-timeMusic>=music.getTimeLength())
			{
				music.loadAudio();
				timeMusic = SDL_GetTicks();
			}
		}
		if (SDL_GetTicks()-timeAudio>=filmStart[numSound].getTimeLength()-2050)
		{
			numSound = (numSound+1)%2;
			filmStart[numSound].clearAudio();
			filmStart[numSound].loadAudio();
			filmStart[numSound].playAudio();
			timeAudio = SDL_GetTicks();
		}
		if (SDL_GetTicks()-timeMusic>=music.getTimeLength())
		{
			music.loadAudio();
			timeMusic = SDL_GetTicks();
		}
	}
	filmStart[0].stopAudio();
	filmStart[1].stopAudio();
	filmStop.loadAudio();
	filmStop.playAudio();
}

void listFilm(SDL_Surface *screen, SDL_Surface *bkgr, SDL_Window *window, Uint32 pos,
				Uint32 tintLeft, Uint32 tintRight, Uint32 tintUp, Uint32 tintDown,
				Uint32 &filmX, Uint32 &filmY, cgfFile &arrows, cgfFile &film,
				wavFile *filmStart, wavFile &filmStop, rawFile *gamePics, cgfFile &modeIcons,
				Uint32 gameMode, cgfFile &playerIcons, Uint32 playerMode, Uint32 numGame,
				fontText &ultraFont, textFile &gameNames, fontText &menuFont,
				textFile &menuText, wavFile &music, Uint32 &timeMusic)
{
	Uint8 numSound = 0;
	filmStart[0].clearAudio();
	filmStart[1].clearAudio();
	filmStart[numSound].loadAudio();
	filmStart[numSound].playAudio();
	Uint32 timeAudio = SDL_GetTicks();
	while (filmY!=0xD6-numGame*0x80)
	{
		Uint32 timer = SDL_GetTicks();
		if (pos == 1)
		{
			filmY -= 0x10;
		}
		else
		{
			filmY += 0x10;
		}
		SDL_BlitSurface(bkgr,NULL,screen,NULL);
		arrows.draw(0,0x102,0x140,0,screen,tintDown,0);
		arrows.draw(2,0x102,0x140,0,screen,tintLeft,0);
		arrows.draw(4,0x102,0x140,0,screen,tintRight,0);
		arrows.draw(6,0x102,0x140,0,screen,tintUp,0);
		for (Uint32 i = 0; i<21; ++i)
		{
			if ((filmY+i*0x80<480)||(filmY+(i+1)*0x80<480))
			{
				gamePics[i].draw(0x1BA,filmY+i*0x80+4,0,0,0,screen,4);
				ultraFont.printText(gameNames[i],0x1BA,filmY+i*0x80+4,screen,4,0);
				film.draw(0,filmX,filmY+i*0x80,0,screen,1,0);
			}
		}
		for (Uint32 i = 0; i<5; ++i)
		{
			menuFont.printText(menuText[i],0x14,0xA8+i*0x2A,screen,1,1);
		}
		modeIcons.draw(gameMode,0x16C,0xAC,0,screen,1,0);
		playerIcons.draw(playerMode,0x16C,0xD9,0,screen,1,0);
		SDL_UpdateWindowSurface(window);
		while(SDL_GetTicks()-timer<30)
		{
			if (SDL_GetTicks()-timeAudio>=filmStart[numSound].getTimeLength()-2050)
			{
				numSound = (numSound+1)%2;
				filmStart[numSound].clearAudio();
				filmStart[numSound].loadAudio();
				filmStart[numSound].playAudio();
				timeAudio = SDL_GetTicks();
			}
			if (SDL_GetTicks()-timeMusic>=music.getTimeLength())
			{
				music.loadAudio();
				timeMusic = SDL_GetTicks();
			}
		}
		if (SDL_GetTicks()-timeAudio>=filmStart[numSound].getTimeLength()-2050)
		{
			numSound = (numSound+1)%2;
			filmStart[numSound].clearAudio();
			filmStart[numSound].loadAudio();
			filmStart[numSound].playAudio();
			timeAudio = SDL_GetTicks();
		}
		if (SDL_GetTicks()-timeMusic>=music.getTimeLength())
		{
			music.loadAudio();
			timeMusic = SDL_GetTicks();
		}
	}
	filmStart[0].stopAudio();
	filmStart[1].stopAudio();
	filmStop.loadAudio();
	filmStop.playAudio();
}

int playMenu(SDL_Window* window)
{
	SDL_Surface *screen = SDL_GetWindowSurface(window);
	SDL_Surface *bkgr = SDL_CreateRGBSurface(0,640,480,32,0,0,0,0);
	SDL_Event e;
	rawFile mainPix (getFullPath("MenuData/mainpix.raw"));
	rawFile hugoLogo(getFullPath("MenuData/hugologo.raw"));
	palFile mainPal(getFullPath("MenuData/mainpal.pal"));
	cgfFile arrows(getFullPath("MenuData/Arrows.cgf"),mainPal);
	cgfFile film(getFullPath("MenuData/Film.cgf"),mainPal);
	wavFile filmStart[2] = {wavFile(getFullPath("MenuData/Filmmove.wav")),
		wavFile(getFullPath("MenuData/Filmmove.wav"))};
	wavFile filmStop(getFullPath("MenuData/Filmstop.wav"));
	rawFile gamePics[21] = {rawFile(getFullPath("MenuData/LABY.RAW")),
							rawFile(getFullPath("MenuData/train.raw")),
							rawFile(getFullPath("MenuData/plane.raw")),
							rawFile(getFullPath("MenuData/forest.raw")),
							rawFile(getFullPath("MenuData/mountain.raw")),
							rawFile(getFullPath("MenuData/minetrack.raw")),
							rawFile(getFullPath("MenuData/SCUBA.RAW")),
							rawFile(getFullPath("MenuData/icecav.raw")),
							rawFile(getFullPath("MenuData/lumberjack.raw")),
							rawFile(getFullPath("MenuData/skateboard.raw")),
							rawFile(getFullPath("MenuData/screen001.raw")),
							rawFile(getFullPath("MenuData/screen002.raw")),
							rawFile(getFullPath("MenuData/moore.raw")),
							rawFile(getFullPath("MenuData/screen000.raw")),
							rawFile(getFullPath("MenuData/screen003.raw")),
							rawFile(getFullPath("MenuData/screen005.raw")),
							rawFile(getFullPath("MenuData/screen007.raw")),
							rawFile(getFullPath("MenuData/screen004.raw")),
							rawFile(getFullPath("MenuData/screen006.raw")),
							rawFile(getFullPath("MenuData/stones.raw")),
							rawFile(getFullPath("MenuData/river.raw"))};
	rawFile optionPics[5] = {rawFile(getFullPath("MenuData/keyboard.raw")),
							rawFile(getFullPath("MenuData/credits.raw")),
							rawFile(getFullPath("MenuData/intro_outro.raw")),
							rawFile(getFullPath("MenuData/pad.raw")),
							rawFile(getFullPath("MenuData/volume.raw"))};
	cgfFile modeIcons(getFullPath("MenuData/ModeIcon.cgf"),mainPal);
	cgfFile playerIcons(getFullPath("MenuData/PlayersIcon.cgf"),mainPal);
	fontText ultraFont(getFullPath("MenuData/UltraFont.cgf"),getFullPath("MenuData/charmapultra.txt"),mainPal);
	fontText creditFont(getFullPath("MenuData/CreditFont.cgf"),getFullPath("MenuData/charmapcredit.txt"),mainPal);
	fontText menuFont(getFullPath("MenuData/MenuFont.cgf"),getFullPath("MenuData/charmapmenu.txt"),mainPal);
	textFile gameNames(getFullPath("MenuData/games.txt"));
	textFile menuText(getFullPath("MenuData/menutext.txt"));
	wavFile music(getFullPath("MenuData/Menyhed-df.wav"));
	wavFile curSound(getFullPath("MenuData/Cursor.wav"));
	wavFile togSound(getFullPath("MenuData/Toggle.wav"));
	textFile optionNames(getFullPath("MenuData/options.txt"));
	textFile optDisplay(getFullPath("MenuData/display.txt"));
	textFile miniGames(getFullPath("MenuData/minigames.txt"));
	textFile programmers(getFullPath("MenuData/programmers.txt"));
	textFile iteWork(getFullPath("MenuData/itework.txt"));
	textFile graphics(getFullPath("MenuData/graphics.txt"));
	textFile sound(getFullPath("MenuData/sound.txt"));
	textFile producers(getFullPath("MenuData/producer.txt"));
	textFile eproducers(getFullPath("MenuData/eproducer.txt"));
	rawFile hiBack(getFullPath("MenuData/hiscoreback.raw"));
	rawFile hiScore(getFullPath("MenuData/highscore.raw"));
	cgfFile hiScreens(getFullPath("MenuData/hiscreens.cgf"));
	wavFile wipeSound(getFullPath("MenuData/Wipe.wav"));
	textFile hiClean(getFullPath("MenuData/hiclean.txt"));
	Uint32 st = 1;
	Uint32 tintLeft = 4, tintRight = 4, tintUp = 4, tintDown = 4;
	Uint32 numGame = 0;
	Uint32 gameMode = 0, playerMode = 0;
	st = st*mainPix.getStatus();
	st = st*hugoLogo.getStatus();
	st = st*mainPal.getStatus();
	st = st*arrows.getStatus();
	st = st*film.getStatus();
	st = st*filmStart[0].getStatus();
	st = st*filmStart[1].getStatus();
	st = st*filmStop.getStatus();
	for (Uint32 i = 0; i<21; ++i)
	{
		st = st*gamePics[i].getStatus();
	}
	for (Uint32 i = 0; i<5; ++i)
	{
		st = st*optionPics[i].getStatus();
	}
	st = st*modeIcons.getStatus();
	st = st*playerIcons.getStatus();
	st = st*ultraFont.getStatus();
	st = st*creditFont.getStatus();
	st = st*menuFont.getStatus();
	st = st*gameNames.getStatus();
	st = st*menuText.getStatus();
	st = st*music.getStatus();
	st = st*curSound.getStatus();
	st = st*togSound.getStatus();
	st = st*optionNames.getStatus();
	st = st*optDisplay.getStatus();
	st = st*miniGames.getStatus();
	st = st*programmers.getStatus();
	st = st*iteWork.getStatus();
	st = st*graphics.getStatus();
	st = st*sound.getStatus();
	st = st*producers.getStatus();
	st = st*eproducers.getStatus();
	st = st*hiBack.getStatus();
	st = st*hiScore.getStatus();
	st = st*hiScreens.getStatus();
	st = st*wipeSound.getStatus();
	st = st*hiClean.getStatus();
	if (!st)
	{
		return 1;
	}
	creditFont.setNullPosX();
	mainPix.draw(0,0,0,0,0,bkgr,1);
	hugoLogo.draw(0x0A,0x0D,0,0,0,bkgr,1);
	SDL_BlitSurface(bkgr,NULL,screen,NULL);
	arrows.draw(0,0x102,0x140,0,screen,tintDown,0);
	arrows.draw(2,0x102,0x140,0,screen,tintLeft,0);
	arrows.draw(4,0x102,0x140,0,screen,tintRight,0);
	arrows.draw(6,0x102,0x140,0,screen,tintUp,0);
	modeIcons.draw(gameMode,0x16C,0xAC,0,screen,1,0);
	playerIcons.draw(playerMode,0x16C,0xD9,0,screen,1,0);
	Uint32 filmX = 0x1A2, filmY = 0x1F6;
	for (Uint32 i = 0; i<5; ++i)
	{
		menuFont.printText(menuText[i],0x14,0xA8+i*0x2A,screen,1,1);
	}
	SDL_UpdateWindowSurface(window);
	music.loadAudio();
	Uint32 timeMusic = SDL_GetTicks();
	music.playAudio();
	listFilm(screen,bkgr,window,1,tintLeft,tintRight,tintUp,tintDown,filmX,filmY,
		arrows,film,filmStart,filmStop,gamePics,modeIcons,gameMode,playerIcons,
		playerMode,numGame,ultraFont,gameNames,menuFont,menuText,music,timeMusic);
	Uint32 exit = 0;
	Uint32 selectMenu = 0;
	Uint32 numMenu = 0;
	tintUp = 1;
	tintLeft = 1;
	tintDown = 1;
	while (SDL_PollEvent(&e));
	while (!exit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					selectMenu = 1;
					numMenu = 4;
				}
				else if ((e.key.keysym.scancode == SDL_SCANCODE_DOWN)||(e.key.keysym.scancode == SDL_SCANCODE_KP_2))
				{
					if (!selectMenu)
					{
						tintUp = 4;
						tintLeft = 4;
						if (numGame == 20)
						{
							numGame = 0;
							listFilm(screen,bkgr,window,0,tintLeft,tintRight,tintUp,tintDown,filmX,filmY,
								arrows,film,filmStart,filmStop,gamePics,modeIcons,gameMode,playerIcons,
								playerMode,numGame,ultraFont,gameNames,menuFont,menuText,music,timeMusic);
							while (SDL_PollEvent(&e));
						}
						else
						{
							numGame++;
							listFilm(screen,bkgr,window,1,tintLeft,tintRight,tintUp,tintDown,filmX,filmY,
								arrows,film,filmStart,filmStop,gamePics,modeIcons,gameMode,playerIcons,
								playerMode,numGame,ultraFont,gameNames,menuFont,menuText,music,timeMusic);
							while (SDL_PollEvent(&e));
						}
						tintUp = 1;
						tintLeft = 1;
						while (SDL_PollEvent(&e));
					}
					else
					{
						curSound.clearAudio();
						curSound.loadAudio();
						curSound.playAudio();
						if (numMenu == 4)
						{
							numMenu = 0;
						}
						else
						{
							numMenu++;
						}
					}
				}
				else if ((e.key.keysym.scancode == SDL_SCANCODE_UP)||(e.key.keysym.scancode == SDL_SCANCODE_KP_8))
				{
					if (!selectMenu)
					{
						tintDown = 4;
						tintLeft = 4;
						if (numGame == 0)
						{
							numGame = 20;
							listFilm(screen,bkgr,window,1,tintLeft,tintRight,tintUp,tintDown,filmX,filmY,
								arrows,film,filmStart,filmStop,gamePics,modeIcons,gameMode,playerIcons,
								playerMode,numGame,ultraFont,gameNames,menuFont,menuText,music,timeMusic);
							while (SDL_PollEvent(&e));
						}
						else
						{
							numGame--;
							listFilm(screen,bkgr,window,0,tintLeft,tintRight,tintUp,tintDown,filmX,filmY,
								arrows,film,filmStart,filmStop,gamePics,modeIcons,gameMode,playerIcons,
								playerMode,numGame,ultraFont,gameNames,menuFont,menuText,music,timeMusic);
							while (SDL_PollEvent(&e));
						}
						tintDown = 1;
						tintLeft = 1;
						while (SDL_PollEvent(&e));
					}
					else
					{
						curSound.clearAudio();
						curSound.loadAudio();
						curSound.playAudio();
						if (numMenu == 0)
						{
							numMenu = 4;
						}
						else
						{
							numMenu--;
						}
					}
				}
				else if ((e.key.keysym.scancode == SDL_SCANCODE_LEFT)||(e.key.keysym.scancode == SDL_SCANCODE_KP_4))
				{
					if (!selectMenu)
					{
						selectMenu = 1;
						tintLeft = 4;
						tintRight = 1;
					}
				}
				else if ((e.key.keysym.scancode == SDL_SCANCODE_RIGHT)||(e.key.keysym.scancode == SDL_SCANCODE_KP_6))
				{
					if (selectMenu)
					{
						selectMenu = 0;
						tintLeft = 1;
						tintRight = 4;
					}
				}
				else if ((e.key.keysym.scancode == SDL_SCANCODE_RETURN)||(e.key.keysym.scancode == SDL_SCANCODE_KP_ENTER))
				{
					if (selectMenu)
					{
						if (numMenu == 0)
						{
							togSound.clearAudio();
							togSound.loadAudio();
							togSound.playAudio();
							gameMode = (gameMode+1)%2;
						}
						else if (numMenu == 1)
						{
							togSound.clearAudio();
							togSound.loadAudio();
							togSound.playAudio();
							playerMode = (playerMode+1)%2;
						}
						else if (numMenu == 2)
						{
							wipeSound.clearAudio();
							wipeSound.loadAudio();
							wipeSound.playAudio();
							startHiscore(window, screen, hiBack, hiScore, hiScreens, arrows, curSound, music,
								timeMusic, ultraFont, creditFont, menuFont, hiClean, gameNames, modeIcons);
							wipeSound.clearAudio();
							wipeSound.loadAudio();
							wipeSound.playAudio();
						}
						else if (numMenu == 3)
						{
							hideFilm(screen,bkgr,window,tintLeft,tintRight,tintUp,tintDown,filmX,filmY,
								arrows,film,filmStart,filmStop,gamePics,modeIcons,gameMode,playerIcons,
								playerMode,ultraFont,gameNames,menuFont,menuText,music,timeMusic);
							startOptions(window, bkgr, screen, arrows, film, filmStart, filmStop, optionPics,
								music, timeMusic, optionNames, ultraFont, creditFont, menuFont, optDisplay,
								miniGames, togSound,iteWork, programmers, graphics, sound, producers,
								eproducers);
							screen = SDL_GetWindowSurface(window);
							listFilm(screen,bkgr,window,1,tintLeft,tintRight,tintUp,tintDown,filmX,filmY,
								arrows,film,filmStart,filmStop,gamePics,modeIcons,gameMode,playerIcons,
								playerMode,numGame,ultraFont,gameNames,menuFont,menuText,music,timeMusic);
							while (SDL_PollEvent(&e));
						}
						else if (numMenu == 4)
						{
							exit = 1;
						}
					}
					else
					{
						togSound.clearAudio();
						togSound.loadAudio();
						togSound.playAudio();
						music.stopAudio();
						music.clearAudio();
						Uint32 score = 0;
						if (numGame == 0)
						{
							if (labyStart(score,gameMode,playerMode,window,screen))
							{
							}
						}
						music.loadAudio();
						timeMusic = SDL_GetTicks();
						music.playAudio();
					}
				}
			}
			else if (e.type == SDL_QUIT)
			{
				exit = 1;
			}
		}
		SDL_BlitSurface(bkgr,NULL,screen,NULL);
		arrows.draw(0,0x102,0x140,0,screen,tintDown,0);
		arrows.draw(2,0x102,0x140,0,screen,tintLeft,0);
		arrows.draw(4,0x102,0x140,0,screen,tintRight,0);
		arrows.draw(6,0x102,0x140,0,screen,tintUp,0);
		for (Uint32 i = 0; i<21; ++i)
		{
			if ((filmY+i*0x80<480)||(filmY+(i+1)*0x80<480))
			{
				if ((numGame==i)&&(!selectMenu))
				{
					gamePics[i].draw(0x1BA,filmY+i*0x80+4,0,0,0,screen,1);
					ultraFont.printText(gameNames[i],0x1BA,filmY+i*0x80+4,screen,1,0);
				}
				else
				{
					gamePics[i].draw(0x1BA,filmY+i*0x80+4,0,0,0,screen,4);
					ultraFont.printText(gameNames[i],0x1BA,filmY+i*0x80+4,screen,4,0);
				}
				film.draw(0,filmX,filmY+i*0x80,0,screen,1,0);
			}
		}
		for (Uint32 i = 0; i<5; ++i)
		{
			if ((numMenu==i)&&(selectMenu))
			{
				menuFont.printText(menuText[i],0x14,0xA8+i*0x2A,screen,2,1);
			}
			else
			{
				menuFont.printText(menuText[i],0x14,0xA8+i*0x2A,screen,1,1);
			}
		}
		modeIcons.draw(gameMode,0x16C,0xAC,0,screen,1,0);
		playerIcons.draw(playerMode,0x16C,0xD9,0,screen,1,0);
		SDL_UpdateWindowSurface(window);
		if (SDL_GetTicks()-timeMusic>=music.getTimeLength())
		{
			music.loadAudio();
			timeMusic = SDL_GetTicks();
		}
	}
	SDL_FreeSurface(bkgr);
	return 0;
}
