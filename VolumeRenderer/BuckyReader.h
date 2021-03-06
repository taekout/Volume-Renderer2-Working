#pragma once
#include "BinaryFileReader.h"

class BuckeyReader : public BinaryFileReader
{
public:
	BuckeyReader(char * filename)
		:BinaryFileReader(filename)
	{
	}
	~BuckeyReader()
	{
	}

	char * ReadData()
	{
		char *content = NULL;
		int count = 0;
		if (fp != NULL) {
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);
			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
		return content;
	}
};
