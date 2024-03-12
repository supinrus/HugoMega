class fontText
{
private:
	cgfFile *cgfFont;
	char map[256];
	Uint32 status;
	Uint32 sz;
	//Uint32 maxWidth;
public:
	fontText(std::string fileName, std::string fileNameMap, palFile &mypal)
	{
		status = 1;
		cgfFont = new cgfFile(fileName,mypal);
		if (cgfFont->getStatus() == 0)
		{
			status = 0;
		}
		else
		{
			std::ifstream fp;
			fp.open(fileNameMap,std::ios::binary);
			if (!fp)
			{
				std::cout<<"Unable to open "<<fileNameMap<<std::endl;
				status = 0;
			}
			else
			{
				fp.seekg(0,fp.end);
				sz = fp.tellg();
				fp.seekg(0,fp.beg);
				if (sz>256)
				{
					std::cout<<"Warning: Size of elements is "<<sz<<" in "<<fileNameMap<<". Reading 256 elements."<<std::endl;
					sz = 256;
				}
				fp.read(map,sz);
				fp.close();
			}
		}
	}
	fontText(std::string fileName, std::string fileNameMap)
	{
		status = 1;
		cgfFont = new cgfFile(fileName);
		if (cgfFont->getStatus() == 0)
		{
			status = 0;
		}
		else
		{
			std::ifstream fp;
			fp.open(fileNameMap,std::ios::binary);
			if (!fp)
			{
				std::cout<<"Unable to open "<<fileNameMap<<std::endl;
				status = 0;
			}
			else
			{
				fp.seekg(0,fp.end);
				sz = fp.tellg();
				fp.seekg(0,fp.beg);
				if (sz>256)
				{
					std::cout<<"Warning: Size of elements is "<<sz<<" in "<<fileNameMap<<". Reading 256 elements."<<std::endl;
					sz = 256;
				}
				fp.read(map,sz);
				fp.close();
				/*maxWidth = 0;
				for (Uint32 i = 0; i<cgfFont->getNum(); ++i)
				{
					if (cgfFont->getWidth(i)>maxWidth)
					{
						maxWidth = cgfFont->getWidth(i);
					}
				}*/
			}
		}
	}
	void printText(std::string text, Uint32 posX, Uint32 posY, SDL_Surface *screen, Uint32 tint, Uint8 anti) const
	{
		Uint32 newPosX = posX;
		for (Uint32 i = 0; i<text.length(); ++i)
		{
			char tmp = text[i];
			Uint32 j = 0;
			if ((tmp>='a')&&(tmp<='z'))
			{
				tmp = tmp+'A'-'a';
			}
			while ((j<sz)&&(map[j]!=tmp))
			{
				++j;
			}
			if (j==sz)
			{
				if (tmp!=0x20)
				{
					Uint32 pp = tmp;
					std::cout<<"Symbol "<<pp<<" not found."<<std::endl;
				}
				newPosX += cgfFont->getWidth(0);
			}
			else
			{
				cgfFont->draw(j,newPosX,posY,0,screen,tint,anti);
				newPosX += cgfFont->getWidth(j);
			}
		}
	}
	Uint32 widthText(std::string text)
	{
		Uint32 sum = 0;
		for (Uint32 i = 0; i<text.length(); ++i)
		{
			char tmp = text[i];
			Uint32 j = 0;
			if ((tmp>='a')&&(tmp<='z'))
			{
				tmp = tmp+'A'-'a';
			}
			while ((j<sz)&&(map[j]!=tmp))
			{
				++j;
			}
			if (j==sz)
			{
				if (tmp!=0x20)
				{
					Uint32 pp = tmp;
					std::cout<<"Symbol "<<pp<<" not found."<<std::endl;
				}
				sum += cgfFont->getWidth(0);
			}
			else
			{
				sum += cgfFont->getWidth(j);
			}
		}
		return sum;
	}
	void setNullPosX()
	{
		Uint32 num = cgfFont->getNum();
		for (Uint32 i = 0; i<num; ++i)
		{
			cgfFont->setPosX(i,0);
		}
	}
	Uint32 getStatus() const
	{
		return status;
	}
	~fontText()
	{
		delete cgfFont;
	}
};
