Uint8 checkEscapeKeyForIntro()
{
	SDL_Event e;
	if (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				return 1;
			}
		}
	}
	return 0;
}

int playIntro(SDL_Window* window)
{
	lzpFile intro(getFullPath("IntroData/ite-media.lzp"));
	wavFile introwav(getFullPath("IntroData/ite-media.wav"));
	rawFile intropic(getFullPath("IntroData/INTRO.RAW"));
	Uint8 st = 0;
	SDL_Surface *screen = SDL_GetWindowSurface(window);
	if ((!intro.getStatus())||(!introwav.getStatus())||(!intropic.getStatus()))
	{
		return 1;
	}
	introwav.loadAudio();
	intro.startTimer();
	while((intro.getFrameNum()<intro.getMaxNum())&&(!st))
	{
		introwav.playAudio();
		intro.loadFrame(intro.getFrameNum(),screen);
		SDL_UpdateWindowSurface(window);
		st = checkEscapeKeyForIntro();
	}
	Uint32 time = SDL_GetTicks();
	while ((!st)&&(SDL_GetTicks()-time)<4000)
	{
		st = checkEscapeKeyForIntro();
		SDL_UpdateWindowSurface(window);
	}
	introwav.stopAudio();
	for (Uint32 i = 256; (i>1)&&(!st); i = i/2)
	{
		time = SDL_GetTicks();
		st = checkEscapeKeyForIntro();
		intropic.draw(0,0,0,0,1,screen,i);
		SDL_UpdateWindowSurface(window);
		while ((SDL_GetTicks()-time<80)&&(!st))
		{
			st = checkEscapeKeyForIntro();
		}
	}
	intropic.draw(0,0,0,0,1,screen,1);
	time = SDL_GetTicks();
	while ((!st)&&(SDL_GetTicks()-time)<2000)
	{
		st = checkEscapeKeyForIntro();
		SDL_UpdateWindowSurface(window);
	}
	for (Uint32 i = 1; (i<256)&&(!st); i = i*2)
	{
		time = SDL_GetTicks();
		st = checkEscapeKeyForIntro();
		intropic.draw(0,0,0,0,1,screen,i);
		SDL_UpdateWindowSurface(window);
		while ((SDL_GetTicks()-time<80)&&(!st))
		{
			st = checkEscapeKeyForIntro();
		}
	}
	return 0;
}
