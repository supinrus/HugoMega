struct hiScoreTable
{
  std::string name;
  Uint32 score;
  Uint8 gameMode;
};

void startHiscore(SDL_Window *window, SDL_Surface *screen, rawFile &hiBack, rawFile &hiScore,
					cgfFile &hiScreens, cgfFile &arrows, wavFile &curSound, wavFile &music,
					Uint32 &timeMusic, fontText &ultraFont, fontText &creditFont,
					fontText &menuFont, textFile &hiClean, textFile &gameNames, cgfFile &modeIcons)
{
	SDL_Event e;
	Uint32 exit = 0;
	Uint32 hiNumGame = 0;
	Uint32 hiNumClear = 0;
	hiScoreTable table[21][6];
	for (Uint32 i = 0; i<21; ++i)
	{
		for (Uint32 j = 0; j<6; ++j)
		{
			table[i][j].name = "NONAME";
			table[i][j].score  = 100 - j*10;
			table[i][j].gameMode = 0;
		}
	}
	while (SDL_PollEvent(&e));
	while (!exit)
	{
		hiBack.draw(0,0,0,0,0,screen,1);
		hiScore.draw(0x26,6,0,0,0,screen,1);
		hiScreens.draw(hiNumGame,0x1d9,0x113,0,screen,1,0);
		arrows.draw(6,0x1db,0xc3,0,screen,1,0);
		arrows.draw(0,0x1db,0x140,0,screen,1,0);
		for (Uint32 i = 0; i<6; ++i)
		{
			std::string numSc = std::to_string(i+1)+".";
			creditFont.printText(numSc,0x14,0xc8+0x2d*i,screen,1,0);
			creditFont.printText(table[hiNumGame][i].name,0x32,0xc8+0x2d*i,screen,1,0);
			creditFont.printText(std::to_string(table[hiNumGame][i].score),
				0x1ad+1-creditFont.widthText(std::to_string(table[hiNumGame][i].score)),0xc8+0x2d*i,screen,1,0);
			modeIcons.draw(table[hiNumGame][i].gameMode,0x1B8,0xC8+i*0x2d,0,screen,1,0);
		}
		std::string hiClStr = hiClean[hiNumClear];
		if (!hiNumClear)
		{
			hiClStr = "F10 - "+hiClStr;
		}
		ultraFont.printText(hiClStr,7,3,screen,1,0);
		menuFont.printText(gameNames[hiNumGame],(0x280-menuFont.widthText(gameNames[hiNumGame]))/2,0x10,screen,1,0);
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
					if (!hiNumClear)
					{
						exit = 1;
					}
					else
					{
						hiNumClear = 0;
					}
				}
				else if ((e.key.keysym.scancode == SDL_SCANCODE_DOWN)||(e.key.keysym.scancode == SDL_SCANCODE_KP_2))
				{
					curSound.clearAudio();
					curSound.loadAudio();
					curSound.playAudio();
					if (hiNumGame==20)
					{
						hiNumGame = 0;
					}
					else
					{
						hiNumGame++;
					}
				}
				else if ((e.key.keysym.scancode == SDL_SCANCODE_UP)||(e.key.keysym.scancode == SDL_SCANCODE_KP_8))
				{
					curSound.clearAudio();
					curSound.loadAudio();
					curSound.playAudio();
					if (hiNumGame==0)
					{
						hiNumGame = 20;
					}
					else
					{
						hiNumGame--;
					}
				}
				else if (e.key.keysym.scancode == SDL_SCANCODE_F10)
				{
					if (!hiNumClear)
					{
						hiNumClear = 1;
					}
					else
					{
						hiNumClear = 0;
						for (Uint32 i = 0; i<6; ++i)
						{
							table[hiNumGame][i].name = "NONAME";
							table[hiNumGame][i].score  = 100 - i*10;
							table[hiNumGame][i].gameMode = 0;
						}
					}
				}
			}
		}
	}
}
