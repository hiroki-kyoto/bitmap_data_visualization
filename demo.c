#include <stdio.h>
#include <math.h>

#include "bmp.h"

#ifndef GRAY_SCALE_BITMAP
#define GRAY_SCALE_BITMAP

typedef unsigned char byte;

// ASSURE [MAT] IS EMPTY BY DEFAULT
void create_matrix(byte*** mat, unsigned long width, unsigned long height)
{
	(*mat) = (byte**)malloc(sizeof(byte*)*height);
	
	for(unsigned long i=0;i<height;i++)
	{
		(*mat)[i] = (byte*)malloc(sizeof(byte)*width);
		memset((*mat)[i], 0, sizeof(byte)*width);
	}
}

void free_matrix(byte** mat, unsigned long height)
{
	for(unsigned long i=0;i<height;i++)
	{
		free(mat[i]);
	}
	free(mat);
}

#endif

int main(int argc, const char** argv)
{
	byte** mat;
	
	unsigned long width = 51;
	unsigned long height  = 43;
	char* opt_file = "opt.bmp";
	
	// col = width; raw = height
	create_matrix(&mat, width, height);

	// modify the matrix
	for(unsigned long j=0;j<width;j++)
	{
		mat[0][j] = 0x33;
	}
	
	for(unsigned long i=1;i<height;i++)
	{
		for(unsigned long j=0;j<width;j++)
		{
			mat[i][j] = 0xAA;
		}
	}
	
	save_data_as_bitmap(mat, width, height, opt_file);
	
	free_matrix(mat, height);
		
	printf("Done.\n");
	
	return 0;
}

