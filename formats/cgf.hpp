class cgfFile
{
private:
	struct cgfHead
	{
		char name[4];
		Uint32 bt;
		Uint32 num;
		Uint32 sizedata;
		Uint32 size;
		Uint32 numpal;
		Uint32 unk;
	};

	struct cgfData
	{
		Uint32 posx;
		Uint32 posy;
		Uint32 width;
		Uint32 height;
		Uint32 unk;
		Uint32 offset;
	};
	cgfHead head;
	cgfData *data;
	Uint32 status;
	Uint8 *pal;
	std::ifstream fp;
	Uint8 testbyte(Uint8 byte, Uint32 antitint)
	{
		Uint8 tmp = byte*antitint;
		if (tmp<byte)
		{
			return 255;
		}
		else
		{
			return tmp;
		}
	}
public:
	cgfFile(std::string fileName)
	{
		pal = 0;
		data = 0;
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
			std::string tmp = head.name;
			tmp = tmp.substr(0,4);
			if (tmp!="CGFF")
			{
				std::cout<<"It is not CGF format in "<<fileName<<std::endl;
				status = 0;
			}
			else
			{
				if (head.numpal==0)
				{
					std::cout<<"CGF file "<<fileName<<" have not palette"<<std::endl;
					status = 0;
				}
				else
				{
					data = new cgfData[head.num+1];
					p = (char *)data;
					fp.read(p,head.num*sizeof(cgfData));
					pal = new Uint8[head.numpal*4];
					fp.seekg(0x1C+head.sizedata+head.size,fp.beg);
					p = (char *)pal;
					fp.read(p,head.numpal*4*sizeof(Uint8));
					data[head.num].offset = head.size;
				}
			}
		}
	}
	cgfFile(std::string fileName, palFile &myPal)
	{
		pal = 0;
		data = 0;
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
			std::string tmp = head.name;
			tmp = tmp.substr(0,4);
			if (tmp!="CGFF")
			{
				std::cout<<"It is not CGF format in "<<fileName<<std::endl;
				status = 0;
			}
			else
			{
				data = new cgfData[head.num+1];
				p = (char *)data;
				fp.read(p,head.num*sizeof(cgfData));
				head.numpal = 256;
				pal = new Uint8[head.numpal*4];
				head.numpal = myPal.getPal(pal,4);
				data[head.num].offset = head.size;
			}
		}
	}
	cgfFile(std::string fileName, cgfFile &myPal)
	{
		pal = 0;
		data = 0;
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
			std::string tmp = head.name;
			tmp = tmp.substr(0,4);
			if (tmp!="CGFF")
			{
				std::cout<<"It is not CGF format in "<<fileName<<std::endl;
				status = 0;
			}
			else
			{
				data = new cgfData[head.num+1];
				p = (char *)data;
				fp.read(p,head.num*sizeof(cgfData));
				head.numpal = 256;
				pal = new Uint8[head.numpal*4];
				head.numpal = myPal.getPal(pal,4);
				data[head.num].offset = head.size;
			}
		}
	}
	cgfFile(std::string fileName, lzpFile &myPal)
	{
		pal = 0;
		data = 0;
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
			std::string tmp = head.name;
			tmp = tmp.substr(0,4);
			if (tmp!="CGFF")
			{
				std::cout<<"It is not CGF format in "<<fileName<<std::endl;
				status = 0;
			}
			else
			{
				data = new cgfData[head.num+1];
				p = (char *)data;
				fp.read(p,head.num*sizeof(cgfData));
				head.numpal = 256;
				pal = new Uint8[head.numpal*4];
				head.numpal = myPal.getPal(pal,4);
				data[head.num].offset = head.size;
			}
		}
	}
	cgfFile(std::string fileName, rawFile &myPal)
	{
		pal = 0;
		data = 0;
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
			std::string tmp = head.name;
			tmp = tmp.substr(0,4);
			if (tmp!="CGFF")
			{
				std::cout<<"It is not CGF format in "<<fileName<<std::endl;
				status = 0;
			}
			else
			{
				data = new cgfData[head.num+1];
				p = (char *)data;
				fp.read(p,head.num*sizeof(cgfData));
				head.numpal = 256;
				pal = new Uint8[head.numpal*4];
				head.numpal = myPal.getPal(pal,4);
				data[head.num].offset = head.size;
			}
		}
	}
	Uint32 getPal(Uint8 *newPal, Uint8 typePal) const
	{
		for (Uint32 i = 0; i<head.numpal; ++i)
		{
			newPal[i*typePal] = pal[i*4];
			newPal[i*typePal+1] = pal[i*4+1];
			newPal[i*typePal+2] = pal[i*4+2];
		}
		return head.numpal;
	}
	Uint32 getStatus() const
	{
		return status;
	}
	Uint32 getWidth(Uint32 num) const
	{
		return data[num].width;
	}
	Uint32 getHeight(Uint32 num) const
	{
		return data[num].height;
	}
	Uint32 getNum() const
	{
		return head.num;
	}
	void setPosX(Uint32 num, Uint32 posX)
	{
		data[num].posx = posX;
	}
	void draw(Uint32 numpic, Uint32 x, Uint32 y, Uint8 scale, SDL_Surface *screen, Uint32 Tint, Uint8 anti)
	{
		if (head.num<=numpic)
		{
			return;
		}
		Uint32 sz = data[numpic+1].offset-data[numpic].offset;
		Uint8 *buf = new Uint8[sz];
		Uint8 *image = new Uint8[data[numpic].width*data[numpic].height*2];
		fp.seekg(0x1C+head.sizedata+data[numpic].offset,fp.beg);
		char *p = (char *)buf;
		fp.read(p,sz*sizeof(Uint8));
		for (Uint32 i = 0, j = 0; i<data[numpic].width*data[numpic].height;)
		{
			sz = buf[j]+buf[j+1]*256+buf[j+2]*256*256+buf[j+3]*256*256*256;
			Uint32 k = 4, nmb;
			while (k<sz)
			{
				if (buf[j+k]==0)
				{
					k++;
					nmb = buf[j+k];
					k++;
					if ((nmb == 0) && (sz == 6))
					{
						nmb = 1;
					}
					while (nmb!=0)
					{
						image[i*2] = 0;
						image[i*2+1] = 0;
						++i;
						--nmb;
					}
				}
				else if (buf[j+k]==1)
				{
					k++;
					nmb = buf[j+k];
					k++;
					while (nmb!=0)
					{
						image[i*2] = buf[j+k];
						image[i*2+1] = buf[j+k+1];
						++i;
						k = k+2;
						--nmb;
					}
				}
				else if (buf[j+k]==2)
				{
					k++;
					nmb = buf[j+k];
					k++;
					while (nmb!=0)
					{
						image[i*2] = buf[j+k];
						image[i*2+1] = buf[j+k+1];
						++i;
						--nmb;
					}
					k = k+2;
				}
				else if (buf[j+k]==3)
				{
					k++;
					nmb = buf[j+k];
					k++;
					while (nmb!=0)
					{
						image[i*2] = buf[j+k];
						image[i*2+1] = 255;
						++i;
						++k;
						--nmb;
					}
				}
				else if (buf[j+k]==4)
				{
					k++;
					nmb = buf[j+k];
					k++;
					while (nmb!=0)
					{
						image[i*2] = buf[j+k];
						image[i*2+1] = 255;
						++i;
						--nmb;
					}
					++k;
				}
			}
			j = j+k;
			while (i%data[numpic].width!=0)
			{
				image[i*2] = 0;
				image[i*2+1] = 0;
				++i;
			}
		}
		for (Uint32 i = 0; i<data[numpic].height; ++i)
		{
			for (Uint32 j = 0; j<data[numpic].width; ++j)
			{
				Uint32 tmpx = data[numpic].posx+j+x;
				Uint32 tmpy = data[numpic].posy+i+y;
				if (scale)
				{
					if ((tmpx*2<640)&&(tmpy*2<480))
					{
						if (!anti)
						{
							set_pixel(screen,tmpx*2,tmpy*2,
								pal[image[(i*data[numpic].width+j)*2]*4+2]/Tint,
								pal[image[(i*data[numpic].width+j)*2]*4+1]/Tint,
								pal[image[(i*data[numpic].width+j)*2]*4]/Tint,
								image[(i*data[numpic].width+j)*2+1]);
							set_pixel(screen,tmpx*2+1,tmpy*2,
								pal[image[(i*data[numpic].width+j)*2]*4+2]/Tint,
								pal[image[(i*data[numpic].width+j)*2]*4+1]/Tint,
								pal[image[(i*data[numpic].width+j)*2]*4]/Tint,
								image[(i*data[numpic].width+j)*2+1]);
							set_pixel(screen,tmpx*2,tmpy*2+1,
								pal[image[(i*data[numpic].width+j)*2]*4+2]/Tint,
								pal[image[(i*data[numpic].width+j)*2]*4+1]/Tint,
								pal[image[(i*data[numpic].width+j)*2]*4]/Tint,
								image[(i*data[numpic].width+j)*2+1]);
							set_pixel(screen,tmpx*2+1,tmpy*2+1,
								pal[image[(i*data[numpic].width+j)*2]*4+2]/Tint,
								pal[image[(i*data[numpic].width+j)*2]*4+1]/Tint,
								pal[image[(i*data[numpic].width+j)*2]*4]/Tint,
								image[(i*data[numpic].width+j)*2+1]);
						}
						else
						{
							set_pixel(screen,tmpx*2,tmpy*2,
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4+2],Tint),
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4+1],Tint),
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4],Tint),
								image[(i*data[numpic].width+j)*2+1]);
							set_pixel(screen,tmpx*2+1,tmpy*2,
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4+2],Tint),
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4+1],Tint),
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4],Tint),
								image[(i*data[numpic].width+j)*2+1]);
							set_pixel(screen,tmpx*2,tmpy*2+1,
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4+2],Tint),
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4+1],Tint),
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4],Tint),
								image[(i*data[numpic].width+j)*2+1]);
							set_pixel(screen,tmpx*2+1,tmpy*2+1,
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4+2],Tint),
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4+1],Tint),
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4],Tint),
								image[(i*data[numpic].width+j)*2+1]);
						}
					}
				}
				else
				{
					if ((tmpx<640)&&(tmpy<480))
					{
						if (!anti)
						{
							set_pixel(screen,tmpx,tmpy,
								pal[image[(i*data[numpic].width+j)*2]*4+2]/Tint,
								pal[image[(i*data[numpic].width+j)*2]*4+1]/Tint,
								pal[image[(i*data[numpic].width+j)*2]*4]/Tint,
								image[(i*data[numpic].width+j)*2+1]);
						}
						else
						{
							set_pixel(screen,tmpx,tmpy,
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4+2],Tint),
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4+1],Tint),
								testbyte(pal[image[(i*data[numpic].width+j)*2]*4],Tint),
								image[(i*data[numpic].width+j)*2+1]);
						}
					}
				}
			}
		}
		delete[] buf;
		delete[] image;
	}
	~cgfFile()
	{
		if (pal)
		{
			delete[] pal;
		}
		if (fp)
		{
			fp.close();
		}
		if (data)
		{
			delete[] data;
		}
	}
};
