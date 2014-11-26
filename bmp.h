// BMP.H

#ifndef BMP_H
#define BMP_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long int dword;

// BMP HEADER

typedef struct tagBITMAPFILEHEADER {
    // BMP file header (14 bytes)
     word bfType;			// file type 
    dword bfSize;			// File Size
     word bfReserved1;		// Must be 0
     word bfReserved2;   	// Must be 0
    dword bfOffBits;		// Offset bit

    // BMP information head (40 bytes)
    dword biSize;			// header size
    dword biWidth;			// image width
    dword biHeight;			// image height
     word biPlanes;			// must be 1
     word biBitCount;		// bits/pixel
    dword biCompression;	// compression type
    dword biSizeImage;		// image body size
    dword biXPelsPerMeter;	// horizontal resolution (pixels/meter)
    dword biYPelsPerMeter;	// vertical resolution (pixels/meter)
    dword biClrUsed;		// colour index
    dword biClrImportant;	// colour index count

	// IF THERE'S PLATE USED, THEN HERE SHOULD BE 4*NumColrs Bytes
	// COLOR TABLE
	
}BMPHeader;


// member function
void init_bmp(BMPHeader* bmp_p, unsigned long width, unsigned long height, int depth)
{
	bmp_p-> bfType = 0x4D42;
	// be careful with the disk alignment
	unsigned long real_width = ((3*width-1)/4+1)*4;
	bmp_p-> bfSize = 0x36 + real_width*height;
	bmp_p-> bfReserved1 = 0x0;
	bmp_p-> bfReserved2 = 0x0;
	bmp_p-> bfOffBits = 0x36;
	
    // BMP INFORMATION HEADER
	bmp_p-> biSize = 0x28;
	bmp_p-> biWidth = width;
	bmp_p-> biHeight = height;
	bmp_p-> biPlanes = 0x01;
	// COLOR DEPTH
	bmp_p-> biBitCount = depth;
	bmp_p-> biCompression = 0;
	bmp_p-> biSizeImage = bmp_p->bfSize - 0x36;
	// RESOLUTION IS IMPORTANT
    bmp_p-> biXPelsPerMeter = 0;
    bmp_p-> biYPelsPerMeter = 0;
    bmp_p-> biClrUsed = 0;
    bmp_p-> biClrImportant = 0;
};

void fill_header(FILE* fp, BMPHeader* hd)
{
	 // BMP file header (14 bytes)
	fwrite(&hd->bfType, sizeof(word), 1, fp);
    fwrite(&hd->bfSize, sizeof(dword), 1, fp);
	fwrite(&hd->bfReserved1, sizeof(word), 1, fp);
	fwrite(&hd->bfReserved2, sizeof(word), 1, fp);
	fwrite(&hd->bfOffBits, sizeof(dword), 1, fp);

    // BMP information head (40 bytes)
	fwrite(&hd->biSize, sizeof(dword), 1, fp);
    fwrite(&hd->biWidth, sizeof(dword), 1, fp);
    fwrite(&hd->biHeight, sizeof(dword), 1, fp);
    fwrite(&hd->biPlanes, sizeof(word), 1, fp);
    fwrite(&hd->biBitCount, sizeof(word), 1, fp);
    fwrite(&hd->biCompression, sizeof(dword), 1, fp);
    fwrite(&hd->biSizeImage, sizeof(dword), 1, fp);
    fwrite(&hd->biXPelsPerMeter, sizeof(dword), 1, fp);
    fwrite(&hd->biYPelsPerMeter, sizeof(dword), 1, fp);
    fwrite(&hd->biClrUsed, sizeof(dword), 1, fp);
    fwrite(&hd->biClrImportant, sizeof(dword), 1, fp);
}

void save_data_as_bitmap(unsigned char** mat, unsigned long width, unsigned long height, char* file_name)
{
	BMPHeader bitmap_h;
	unsigned short depth = 0x18;
	
	init_bmp(&bitmap_h, width, height, depth);
	
	FILE *fp = fopen(file_name, "w+b");
	
	// fill header
	// be careful with the memory alignment
	fill_header(fp, &bitmap_h);
	
	// write data to colour matrix in file
	// be careful! data are put in the file upside down
	unsigned char seg = 0x00;
	
	// be careful with the disk alignment
	unsigned long real_width = ((3*width-1)/4+1)*4;
	int edge_n = real_width - 3*width;
	
	for(unsigned long i=0;i<height;i++)
	{
		for(unsigned long j=0;j<width;j++)
		{
			fwrite(&mat[height-1-i][j], sizeof(unsigned char), 1, fp);
			fwrite(&mat[height-1-i][j], sizeof(unsigned char), 1, fp);
			fwrite(&mat[height-1-i][j], sizeof(unsigned char), 1, fp);
		}
		for(int j=0;j<edge_n;j++)
		{
			fwrite(&seg, sizeof(unsigned char), 1, fp);
		}
	}
	
	// close file 
	fclose(fp);
}


#endif

