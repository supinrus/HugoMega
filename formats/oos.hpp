class oosFile
{
private:
	struct oosHead
	{
		char name[8];
		Uint32 ver;
		Uint32 unk1;
		Uint32 unk2;
		Uint32 ofst;
		Uint32 start;
	};
	oosHead head;
	Uint8 *buf;
	Uint32 sz;
	Uint32 status;
public:
	oosFile(std::string fileName)
	{
		buf = 0;
		status = 1;
		std::ifstream fp;
		fp.open(fileName.c_str(),std::ios::binary);
		if (!fp)
		{
			std::cout<<"Unable to open "<<fileName<<std::endl;
			status = 0;
		}
		else
		{
			char *p = (char *)&head;
			fp.read(p,sizeof(head));
			std::string tmp=head.name;
			tmp = tmp.substr(0,8);
			if (tmp!="SYNC2000")
			{
				std::cout<<"It is not OOS format in "<<fileName<<std::endl;
				status = 0;
			}
			else
			{
				fp.seekg(head.ofst,fp.beg);
				p = (char *)&sz;
				fp.read(p,sizeof(Uint32));
				buf = new Uint8[sz];
				fp.seekg(head.start,fp.beg);
				p = (char *)buf;
				fp.read(p,sz*sizeof(Uint8));
			}
			fp.close();
		}
	}
	Uint32 getStatus() const
	{
		return status;
	}
	void playOos(wavFile &speak, cgfFile &sync, Uint32 syncX, Uint32 syncY, rawFile &back, SDL_Window *window, SDL_Surface *screen)
	{
		speak.clearAudio();
		speak.loadAudio();
		const Uint32 timeShift = 120;
		Uint32 startTime = SDL_GetTicks();
		speak.playAudio();
		Uint32 num;
		while ((num = (SDL_GetTicks()-startTime)/timeShift)<sz)
		{
			back.draw(0,0,0,0,1,screen,1);
			sync.draw(buf[num]-1,syncX,syncY,1,screen,1,0);
			SDL_UpdateWindowSurface(window);
		}
	}
	~oosFile()
	{
		if (buf)
		{
			delete[] buf;
		}
	}
};
