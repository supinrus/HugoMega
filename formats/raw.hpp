class rawFile
{
private:
	struct rawHead
	{
		char name[6];
		Uint16 version;
		Uint16 width;
		Uint16 height;
		Uint16 numpal;
		Uint16 unk[9];
	};
	rawHead head;
	Uint32 status;
	Uint8 *pal;
	std::ifstream fp;
public:
	rawFile(std::string fileName)
	{
		status = 1;
		pal = 0;
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
			tmp = tmp.substr(0,6);
			if (tmp != "mhwanh")
			{
				std::cout<<"It is not RAW format in "<<fileName<<std::endl;
				status = 0;
			}
			else
			{
				head.version = (head.version%256)*256+(head.version/256);
				head.width = (head.width%256)*256+(head.width/256);
				head.height = (head.height%256)*256+(head.height/256);
				head.numpal = (head.numpal%256)*256+(head.numpal/256);
				pal = new Uint8[head.numpal*3];
				p = (char *)pal;
				fp.read(p,head.numpal*3*sizeof(Uint8));
			}
		}
	}
	Uint32 getPal(Uint8 *newPal, Uint8 typePal) const
	{
		for (Uint32 i = 0; i<head.numpal; ++i)
		{
			newPal[i*typePal] = pal[i*3];
			newPal[i*typePal+1] = pal[i*3+1];
			newPal[i*typePal+2] = pal[i*3+2];
		}
		return head.numpal;
	}
	Uint32 getStatus() const
	{
		return status;
	}
	void draw(Uint32 posx, Uint32 posy, Uint32 startx, Uint32 starty, Uint8 scale, SDL_Surface *screen, Uint32 Tint)
	{
		Uint8 *buf = new Uint8[head.height*head.width];
		fp.seekg(0x20+head.numpal*3,fp.beg);
		char *p = (char *)buf;
		fp.read(p,head.height*head.width*sizeof(Uint8));
		for (Uint32 i = starty; i<head.height; ++i)
		{
			for (Uint32 j = startx; j<head.width; ++j)
			{
				if (scale)
				{
					if ((posy*2+i*2<480)&&(posx*2+j*2<640))
					{
						set_pixel(screen,posx+j*2,posy+i*2,pal[buf[i*head.width+j]*3]/Tint,pal[buf[i*head.width+j]*3+1]/Tint,pal[buf[i*head.width+j]*3+2]/Tint,255);
						set_pixel(screen,posx+j*2+1,posy+i*2,pal[buf[i*head.width+j]*3]/Tint,pal[buf[i*head.width+j]*3+1]/Tint,pal[buf[i*head.width+j]*3+2]/Tint,255);
						set_pixel(screen,posx+j*2,posy+i*2+1,pal[buf[i*head.width+j]*3]/Tint,pal[buf[i*head.width+j]*3+1]/Tint,pal[buf[i*head.width+j]*3+2]/Tint,255);
						set_pixel(screen,posx+j*2+1,posy+i*2+1,pal[buf[i*head.width+j]*3]/Tint,pal[buf[i*head.width+j]*3+1]/Tint,pal[buf[i*head.width+j]*3+2]/Tint,255);
					}
				}
				else
				{
					if ((posy+i<480)&&(posx+j<640))
					{
						set_pixel(screen,posx+j,posy+i,pal[buf[i*head.width+j]*3]/Tint,pal[buf[i*head.width+j]*3+1]/Tint,pal[buf[i*head.width+j]*3+2]/Tint,255);
					}
				}
			}
		}
		delete[] buf;
	}
	~rawFile()
	{
		if (pal)
		{
			delete[] pal;
		}
		if (fp)
		{
			fp.close();
		}
	}
};
