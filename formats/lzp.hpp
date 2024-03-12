class lzpFile
{
private:
	struct lzpHead{
		Uint32 num;
		Uint32 width;
		Uint32 height;
		Uint32 fps;
		Uint32 unk[4];
		Uint8 pal[768];
	};
	lzpHead head;
	Uint32 status;
	Uint32 *offset;
	Uint32 timer;
	std::ifstream fp;
public:
	lzpFile(std::string fileName)
	{
		status = 1;
		timer = 0;
		offset = 0;
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
			offset = new Uint32[head.num+1];
			fp.seekg(0,fp.end);
			offset[head.num] = fp.tellg();
			offset[head.num] -= head.num*sizeof(Uint32);
			fp.seekg(offset[head.num],fp.beg);
			p = (char *)offset;
			fp.read(p,head.num*sizeof(Uint32));
		}
	}
	Uint32 getStatus() const
	{
		return status;
	}
	void startTimer()
	{
		timer = SDL_GetTicks();
	}
	Uint32 getFrameNum() const
	{
		return ((SDL_GetTicks()-timer)*head.fps)/1000;
	}
	Uint32 getMaxNum() const
	{
		return head.num;
	}
	Uint32 getPal(Uint8 *newPal, Uint8 typePal) const
	{
		for (Uint32 i = 0; i<256; ++i)
		{
			newPal[i*typePal] = head.pal[i*3];
			newPal[i*typePal+1] = head.pal[i*3+1];
			newPal[i*typePal+2] = head.pal[i*3+2];
		}
		return 256;
	}
	void loadFrame(Uint32 frnum, SDL_Surface *screen)
	{
		Uint8 *image = new Uint8[head.width*head.height];
		Uint32 sz;
		Uint8 *buf;
		Uint8 *zbuf = new Uint8[0x1000];
		frnum = frnum%head.num;
		fp.seekg(offset[frnum],fp.beg);
		char *p = (char *)&sz;
		fp.read(p,sizeof(Uint32));
		buf = new Uint8[sz+1];
		p = (char *)buf;
		fp.read(p,sz*sizeof(Uint8));
		for (Uint32 i = 0,j = 0, k = 0xFEE; j<head.width*head.height;)
		{
			Uint32 bt = buf[i]+0xFF00;
			++i;
			while ((bt>0xFF) && (j<head.width*head.height))
			{
				if ((bt&1) != 0)
				{
					bt = bt/2;
					image[j] = buf[i];
					zbuf[k] = buf[i];
					++i;
					++j;
					++k;
					k = k & 0xFFF;
				}
				else
				{
					bt = bt/2;
					Uint32 b1 = buf[i];
					Uint32 b2 = buf[i+1];
					i = i+2;
					Uint32 rz = b2/16;
					b1 = b1+0x100*rz;
					b2 = b2%16;
					b2 = b2+3;
					while (b2!=0)
					{
						image[j] = zbuf[b1];
						zbuf[k] = zbuf[b1];
						++j;
						++k;
						--b2;
						++b1;
						k = k&0xFFF;
						b1 = b1&0xFFF;
					}
				}
			}
		}
		for (Uint32 i = 0; i<head.height; ++i)
   			for (Uint32 j = 0; j<head.width; ++j)
			{
				set_pixel(screen,j*2,i*2,head.pal[image[i*head.width+j]*3],head.pal[image[i*head.width+j]*3+1],head.pal[image[i*head.width+j]*3+2],255);
				set_pixel(screen,j*2,i*2+1,head.pal[image[i*head.width+j]*3],head.pal[image[i*head.width+j]*3+1],head.pal[image[i*head.width+j]*3+2],255);
				set_pixel(screen,j*2+1,i*2,head.pal[image[i*head.width+j]*3],head.pal[image[i*head.width+j]*3+1],head.pal[image[i*head.width+j]*3+2],255);
				set_pixel(screen,j*2+1,i*2+1,head.pal[image[i*head.width+j]*3],head.pal[image[i*head.width+j]*3+1],head.pal[image[i*head.width+j]*3+2],255);
			}
		delete[] buf;
		delete[] zbuf;
		delete[] image;
	}
	~lzpFile()
	{
		if (offset)
		{
			delete[] offset;
		}
		if (fp)
		{
			fp.close();
		}
	}
};
