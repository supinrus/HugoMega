void listFilmOpt(SDL_Window *window, SDL_Surface *bkgr, SDL_Surface *screen, Uint32 pos, Uint32 numOpt,
				Uint32 tintLeft, Uint32 tintRight, Uint32 tintUp, Uint32 tintDown,
				Uint32 &filmX, Uint32 &filmY, cgfFile &arrows, cgfFile &film,
				wavFile *filmStart, wavFile &filmStop, rawFile *optionPics,
				wavFile &music, Uint32 &timeMusic, textFile &optionNames,
				fontText &ultraFont)
{
	Uint8 numSound = 0;
	filmStart[0].clearAudio();
	filmStart[1].clearAudio();
	filmStart[numSound].loadAudio();
	filmStart[numSound].playAudio();
	Uint32 timeAudio = SDL_GetTicks();
	while (filmY!=0xD6-numOpt*0x80)
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
		for (Uint32 i = 0; i<3; ++i)
		{
			if ((filmY+i*0x80<480)||(filmY+(i+1)*0x80<480))
			{
				optionPics[i].draw(0x1BA,filmY+i*0x80+4,0,0,0,screen,4);
				ultraFont.printText(optionNames[i],0x1BA,filmY+i*0x80+4,screen,4,0);
				film.draw(0,filmX,filmY+i*0x80,0,screen,1,0);
			}
		}
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

void hideFilmOpt(SDL_Window *window, SDL_Surface *bkgr, SDL_Surface *screen,
				Uint32 tintLeft, Uint32 tintRight, Uint32 tintUp, Uint32 tintDown,
				Uint32 &filmX, Uint32 &filmY, cgfFile &arrows, cgfFile &film,
				wavFile *filmStart, wavFile &filmStop, rawFile *optionPics,
				wavFile &music, Uint32 &timeMusic, textFile &optionNames,
				fontText &ultraFont)
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
		for (Uint32 i = 0; i<3; ++i)
		{
			if ((filmY+i*0x80<480)||(filmY+(i+1)*0x80<480))
			{
				optionPics[i].draw(0x1BA,filmY+i*0x80+4,0,0,0,screen,4);
				ultraFont.printText(optionNames[i],0x1BA,filmY+i*0x80+4,screen,4,0);
				film.draw(0,filmX,filmY+i*0x80,0,screen,1,0);
			}
		}
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

void startOptions(SDL_Window *window, SDL_Surface *bkgr, SDL_Surface *screen, cgfFile &arrows, cgfFile &film,
				wavFile *filmStart, wavFile &filmStop, rawFile *optionPics, wavFile &music,
				Uint32 &timeMusic, textFile &optionNames, fontText &ultraFont, fontText &creditFont,
				fontText &menuFont, textFile &optDisplay, textFile &miniGames, wavFile &togSound,
				textFile &iteWork, textFile &programmers, textFile &graphics, textFile &sound,
				textFile &producers, textFile &eproducers)
{
	SDL_Event e;
	Uint32 numOpt = 0;
	Uint32 tintLeft = 4, tintRight = 4, tintUp = 4, tintDown = 4;
	Uint32 exit = 0;
	Uint32 selectOpt = 0;
	Uint32 filmX = 0x1A2, filmY = 0x1F6;
	listFilmOpt(window, bkgr, screen, 1, numOpt, tintLeft, tintRight, tintUp, tintDown,
				filmX, filmY, arrows, film, filmStart, filmStop, optionPics, music, timeMusic,
				optionNames, ultraFont);
	while (SDL_PollEvent(&e));
	tintLeft = 1;
	tintUp = 1;
	tintDown = 1;
	Uint32 creditTime;
	while (!exit)
	{
		SDL_BlitSurface(bkgr,NULL,screen,NULL);
		arrows.draw(0,0x102,0x140,0,screen,tintDown,0);
		if (numOpt!=1) arrows.draw(2,0x102,0x140,0,screen,tintLeft,0);
		if (numOpt!=1) arrows.draw(4,0x102,0x140,0,screen,tintRight,0);
		arrows.draw(6,0x102,0x140,0,screen,tintUp,0);
		for (Uint32 i = 0; i<3; ++i)
		{
			if ((filmY+i*0x80<480)||(filmY+(i+1)*0x80<480))
			{
				if (numOpt==i)
				{
					optionPics[i].draw(0x1BA,filmY+i*0x80+4,0,0,0,screen,1);
					ultraFont.printText(optionNames[i],0x1BA,filmY+i*0x80+4,screen,1,0);
				}
				else
				{
					optionPics[i].draw(0x1BA,filmY+i*0x80+4,0,0,0,screen,4);
					ultraFont.printText(optionNames[i],0x1BA,filmY+i*0x80+4,screen,4,0);
				}
				film.draw(0,filmX,filmY+i*0x80,0,screen,1,0);
			}
		}
		if (numOpt == 0)
		{
			std::string dispStr = optDisplay[0]+": "+optDisplay[options.display+1];
			if (!selectOpt)
			{
				menuFont.printText(dispStr,(0x1A2-menuFont.widthText(dispStr))/2,200,screen,1,1);
			}
			else
			{
				menuFont.printText(dispStr,(0x1A2-menuFont.widthText(dispStr))/2,200,screen,2,1);
			}
		}
		else if (numOpt == 1)
		{
			Uint32 testTime = SDL_GetTicks()-creditTime;
			if (((testTime/2000)%9 == 0)||((testTime/2000)%9 == 1)||((testTime/2000)%9 == 2))
			{
				menuFont.printText(iteWork[0],(0x1A2-menuFont.widthText(iteWork[0]))/2,200,screen,1,1);
				for (int i = 0; i<3; ++i)
				{
					creditFont.printText(programmers[((testTime/2000)%9)*3+i],(0x1A2-creditFont.widthText(programmers[((testTime/2000)%9)*3+i]))/2,250+35*i,screen,1,1);
				}
			}
			else if (((testTime/2000)%9 == 3)||((testTime/2000)%9 == 4)||((testTime/2000)%9 == 5))
			{
				menuFont.printText(iteWork[1],(0x1A2-menuFont.widthText(iteWork[1]))/2,200,screen,1,1);
				if (((testTime/2000)%9 == 3)||((testTime/2000)%9 == 4))
				{
					for (int i = 0; i<3; ++i)
					{
						creditFont.printText(graphics[((testTime/2000)%9-3)*3+i],(0x1A2-creditFont.widthText(graphics[((testTime/2000)%9-3)*3+i]))/2,250+35*i,screen,1,1);
					}
				}
				else
				{
					for (int i = 0; i<2; ++i)
					{
						creditFont.printText(graphics[((testTime/2000)%9-3)*3+i],(0x1A2-creditFont.widthText(graphics[((testTime/2000)%9-3)*3+i]))/2,250+35*i,screen,1,1);
					}
				}
			}
			else if ((testTime/2000)%9 == 6)
			{
				menuFont.printText(iteWork[2],(0x1A2-menuFont.widthText(iteWork[2]))/2,200,screen,1,1);
				for (int i = 0; i<2; ++i)
				{
					creditFont.printText(sound[i],(0x1A2-creditFont.widthText(sound[i]))/2,250+35*i,screen,1,1);
				}
			}
			else if ((testTime/2000)%9 == 7)
			{
				menuFont.printText(iteWork[3],(0x1A2-menuFont.widthText(iteWork[3]))/2,200,screen,1,1);
				for (int i = 0; i<1; ++i)
				{
					creditFont.printText(producers[i],(0x1A2-creditFont.widthText(producers[i]))/2,250+35*i,screen,1,1);
				}
			}
			else if ((testTime/2000)%9 == 8)
			{
				menuFont.printText(iteWork[4],(0x1A2-menuFont.widthText(iteWork[4]))/2,200,screen,1,1);
				for (int i = 0; i<1; ++i)
				{
					creditFont.printText(eproducers[i],(0x1A2-creditFont.widthText(eproducers[i]))/2,250+35*i,screen,1,1);
				}
			}
		}
		else if (numOpt == 2)
		{
			menuFont.printText(miniGames[0],(0x1A2-menuFont.widthText(miniGames[0]))/2,200,screen,1,1);
			if (!selectOpt)
			{
				creditFont.printText(miniGames[options.numMiniGame+1],(0x1A2-creditFont.widthText(miniGames[options.numMiniGame+1]))/2,240,screen,1,1);
			}
			else
			{
				creditFont.printText(miniGames[options.numMiniGame+1],(0x1A2-creditFont.widthText(miniGames[options.numMiniGame+1]))/2,240,screen,2,1);
			}
		}
		SDL_UpdateWindowSurface(window);
		if (SDL_GetTicks()-timeMusic>=music.getTimeLength())
		{
			music.loadAudio();
			timeMusic = SDL_GetTicks();
		}
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					exit = 1;
				}
				else if ((e.key.keysym.scancode == SDL_SCANCODE_DOWN)||(e.key.keysym.scancode == SDL_SCANCODE_KP_2))
				{
					if (!selectOpt)
					{
						tintUp = 4;
						tintLeft = 4;
						if (numOpt == 2)
						{
							numOpt = 0;
							listFilmOpt(window, bkgr, screen, 2, numOpt, tintLeft, tintRight, tintUp, tintDown,
								filmX, filmY, arrows, film, filmStart, filmStop, optionPics, music, timeMusic,
								optionNames, ultraFont);
							while (SDL_PollEvent(&e));
						}
						else
						{
							++numOpt;
							listFilmOpt(window, bkgr, screen, 1, numOpt, tintLeft, tintRight, tintUp, tintDown,
								filmX, filmY, arrows, film, filmStart, filmStop, optionPics, music, timeMusic,
								optionNames, ultraFont);
							while (SDL_PollEvent(&e));
						}
						tintUp = 1;
						tintLeft = 1;
						if (numOpt == 1)
						{
							creditTime = SDL_GetTicks();
						}
						while (SDL_PollEvent(&e));
					}
				}
				else if ((e.key.keysym.scancode == SDL_SCANCODE_UP)||(e.key.keysym.scancode == SDL_SCANCODE_KP_8))
				{
					if (!selectOpt)
					{
						tintDown = 4;
						tintLeft = 4;
						if (numOpt == 0)
						{
							numOpt = 2;
							listFilmOpt(window, bkgr, screen, 1, numOpt, tintLeft, tintRight, tintUp, tintDown,
								filmX, filmY, arrows, film, filmStart, filmStop, optionPics, music, timeMusic,
								optionNames, ultraFont);
							while (SDL_PollEvent(&e));
						}
						else
						{
							--numOpt;
							listFilmOpt(window, bkgr, screen, 2, numOpt, tintLeft, tintRight, tintUp, tintDown,
								filmX, filmY, arrows, film, filmStart, filmStop, optionPics, music, timeMusic,
								optionNames, ultraFont);
							while (SDL_PollEvent(&e));
						}
						tintDown = 1;
						tintLeft = 1;
						if (numOpt == 1)
						{
							creditTime = SDL_GetTicks();
						}
						while (SDL_PollEvent(&e));
					}
				}
				else if ((e.key.keysym.scancode == SDL_SCANCODE_LEFT)||(e.key.keysym.scancode == SDL_SCANCODE_KP_4))
				{
					if ((!selectOpt)&&(numOpt!=1))
					{
						selectOpt = 1;
						tintLeft = 4;
						tintRight = 1;
						tintUp = 4;
						tintDown = 4;
					}
				}
				else if ((e.key.keysym.scancode == SDL_SCANCODE_RIGHT)||(e.key.keysym.scancode == SDL_SCANCODE_KP_6))
				{
					if (selectOpt)
					{
						selectOpt = 0;
						tintLeft = 1;
						tintRight = 4;
						tintUp = 1;
						tintDown = 1;
					}
				}
				else if ((e.key.keysym.scancode == SDL_SCANCODE_RETURN)||(e.key.keysym.scancode == SDL_SCANCODE_KP_ENTER))
				{
					if (selectOpt)
					{
						if (numOpt == 0)
						{
							togSound.clearAudio();
							togSound.loadAudio();
							togSound.playAudio();
							if (options.display == 0)
							{
								options.display = 1;
								SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
							}
							else
							{
								options.display  = 0;
								SDL_SetWindowFullscreen(window,0);
							}
							screen = SDL_GetWindowSurface(window);
						}
						else if (numOpt == 2)
						{
							togSound.clearAudio();
							togSound.loadAudio();
							togSound.playAudio();
							options.numMiniGame = (options.numMiniGame+1)%7;
						}
					}
				}
			}
		}
	}
	hideFilmOpt(window, bkgr, screen, tintLeft, tintRight, tintUp, tintDown,
				filmX, filmY, arrows, film, filmStart, filmStop, optionPics, music, timeMusic,
				optionNames, ultraFont);
}
