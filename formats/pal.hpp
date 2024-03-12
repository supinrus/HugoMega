class palFile
{
private:
	Uint32 status;
	Uint8 *pal;
public:
	palFile(std::string fileName)
	{
		std::ifstream fp;
		pal = 0;
		status = 1;
		char text[16];
		fp.open(fileName.c_str(),std::ios::binary);
		if (!fp)
		{
			std::cout<<"Unable to open "<<fileName<<std::endl;
			status = 0;
		}
		else
		{
			fp.read(text,16);
			std::string tmp = text;
			tmp = tmp.substr(0,10);
			if (tmp=="CPAL768STD")
			{
				pal = new Uint8[768];
				char *p  = (char*)pal;
				fp.seekg(10,fp.beg);
				fp.read(p,768);
			}
			else
			{
				std::cout<<"It is not PAL format in "<<fileName<<std::endl;
				status = 0;
			}
		}
	}
	Uint32 getPal(Uint8 *newPal, Uint8 typePal) const
	{
		for (Uint32 i = 0; i<256; ++i)
		{
			newPal[i*typePal] = pal[i*3];
			newPal[i*typePal+1] = pal[i*3+1];
			newPal[i*typePal+2] = pal[i*3+2];
		}
		return 256;
	}
	Uint32 getStatus() const
	{
		return status;
	}
	~palFile()
	{
		if (pal)
		{
			delete[] pal;
		}
	}
};
