#include<stdio.h>
#include<fcntl.h>
#include<io.h>
#include<graphics.h>
#include"hz.h"


void Read_Asc16(char key, unsigned char* buf)
{
	int handle;
	long address;
	handle = open("hzk\\asc16", O_RDONLY | O_BINARY);
	address = key * 16l;
	lseek(handle, address, SEEK_SET);
	read(handle, buf, 16);
	close(handle);
}


void Put_Asc16_Size(int cx, int cy, int xsize, int ysize, char key, int fcolor)
{
	int a, b, o, k;
	unsigned char buf[16];
	Read_Asc16(key, buf);
	for (a = 0; a < 16; a++)
		for (o = 1; o <= ysize; o++)
			for (b = 0; b < 8; b++)
				for (k = 1; k <= xsize; k++)
					if ((buf[a] >> 7 - b) & 1)
						//video_buffer[(((cy+o+a*ysize)<<8)+((cy+o+a*ysize)<<6))+cx+xsize*b+k]=fcolor;
						putpixel(cx + b * xsize + k, cy + o + a * ysize, fcolor);
}