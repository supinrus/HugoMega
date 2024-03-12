class textFile
{
private:
	Uint32 status;
	std::string *str;
	Uint32 num;
public:
	textFile(std::string fileName)
	{
		status = 1;
		std::ifstream fp;
		str = 0;
		num = 0;
		fp.open(fileName);
		if (!fp)
		{
			std::cout<<"Unable to open "<<fileName<<std::endl;
			status = 0;
		}
		else
		{
			char c, d;
			while (fp.get(c))
			{
				if (c == 0x0A)
				{
					num += 1;
				}
				d = c;
			}
			if (d != 0x0A)
			{
				num += 1;
			}
			fp.close();
			fp.open(fileName);
			str = new std::string[num];
			str[0] = "";
			for (Uint32 i = 0; i<num;)
			{
				while (fp.get(c))
				{
					if (c == 0x0A)
					{
						i += 1;
						if (i<num)
						{
							str[i] = "";
						}
					}
					else
					{
						str[i] += c;
					}
				}
				if (i<num)
				{
					++i;
				}
			}
			fp.close();
		}
	}
	Uint32 getStatus() const
	{
		return status;
	}
	std::string operator[](Uint32 num) const
	{
		return str[num];
	}
	~textFile()
	{
		if (str)
		{
			delete[] str;
		}
	}
};
