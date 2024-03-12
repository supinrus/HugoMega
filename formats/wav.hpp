class wavFile
{
private:
	SDL_AudioSpec wavspec;
	SDL_AudioDeviceID wavdev;
	Uint32 wavlen;
	Uint8 *wavbuf;
	Uint32 status;
public:
	wavFile(std::string fileName)
	{
		status = 1;
		if (SDL_LoadWAV(fileName.c_str(),&wavspec,&wavbuf,&wavlen) == NULL)
		{
			std::cout<<"Unable to open "<<fileName<<std::endl;
			status = 0;
		}
		else
		{
			wavdev = SDL_OpenAudioDevice(NULL,0,&wavspec,NULL,0);
		}
	}
	void playAudio()
	{
		SDL_PauseAudioDevice(wavdev,0);
	}
	void loadAudio()
	{
		SDL_QueueAudio(wavdev,wavbuf,wavlen);
	}
	void clearAudio()
	{
		SDL_ClearQueuedAudio(wavdev);
	}
	void stopAudio()
	{
		SDL_PauseAudioDevice(wavdev,1);
	}
	Uint32 getTimeLength() const
	{
		Uint32 tmp = wavlen*1000;
		tmp = tmp/wavspec.freq;
		return tmp;
	}
	Uint32 getStatus() const
	{
		return status;
	}
	~wavFile()
	{
		if (status)
		{
			SDL_CloseAudioDevice(wavdev);
			SDL_FreeWAV(wavbuf);
		}
	}
};
