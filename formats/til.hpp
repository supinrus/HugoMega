class tilFile
{
private:
	struct tilHead
	{
		Uint32 size;
		Uint16 unk1;
		Uint16 numfr;
		Uint16 width;
		Uint16 height;
		Uint16 minfps;
		Uint16 fps;
		Uint8 unk2[4];
		Uint16 wi2;
		Uint16 he2;
		Uint8 unk3[8];
		Uint8 pal[0x300];
	};
	tilHead head;
	Uint32 status;
	std::ifstream fp;
public:
	tilFile(std::string fileName)
	{
		status = 1;
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
			head.pal[0] = 0;
			head.pal[1] = 0;
			head.pal[2] = 0;
			head.wi2 = head.wi2/256+(head.he2%256)*256;
			head.he2 = head.he2/256+(head.unk3[0]%256)*256;
		}
	}
	Uint32 getStatus()
	{
		return status;
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
		Uint16 *buf = new Uint16[head.wi2*head.he2];
		Uint8 *image = new Uint8[head.width*head.height];
		fp.seekg(0x320+frnum*head.wi2*head.he2*2,fp.beg);
		char *p = (char *) buf;
		fp.read(p,head.wi2*head.he2*sizeof(Uint16));
		for (Uint32 i = 0; i<head.he2; ++i)
		{
			for (Uint32 j = 0; j<head.wi2; ++j)
			{
				Uint16 z = buf[i*head.wi2+j];
				for (Uint32 k = 0; k<0x10; ++k)
				{
					fp.seekg(0x320+(head.numfr+2)*head.wi2*head.he2*2+k*16+z*256,fp.beg);
					p = (char *)image+head.width*i*16+j*16+k*head.width;
					fp.read(p,0x10*sizeof(Uint8));
				}
			}
		}
		for (Uint32 i = 0; i<head.height; ++i)
		{
			for (Uint32 j = 0; j<head.width; ++j)
			{
				set_pixel(screen,j*2,i*2,head.pal[image[i*head.width+j]*3],head.pal[image[i*head.width+j]*3+1],head.pal[image[i*head.width+j]*3+2],255);
				set_pixel(screen,j*2,i*2+1,head.pal[image[i*head.width+j]*3],head.pal[image[i*head.width+j]*3+1],head.pal[image[i*head.width+j]*3+2],255);
				set_pixel(screen,j*2+1,i*2,head.pal[image[i*head.width+j]*3],head.pal[image[i*head.width+j]*3+1],head.pal[image[i*head.width+j]*3+2],255);
				set_pixel(screen,j*2+1,i*2+1,head.pal[image[i*head.width+j]*3],head.pal[image[i*head.width+j]*3+1],head.pal[image[i*head.width+j]*3+2],255);
			}
		}
		delete[] buf;
		delete[] image;
	}
	Uint32 getNum()
	{
		Uint32 ans = head.numfr;
		return ans;
	}
	~tilFile()
	{
		if (fp)
		{
			fp.close();
		}
	}
};
