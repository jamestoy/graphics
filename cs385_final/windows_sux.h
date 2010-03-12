/*
 *  windows_sux.h
 *  cs385_final
 *
 *  Created by james toy on 3/11/10.
 *  Copyright 2010 union college. All rights reserved.
 *
 */

typedef struct tagBITMAPFILEHEADER {
	int bfType; 
	double bfSize; 
	int bfReserved1; 
	int bfReserved2; 
	double bfOffBits; 
} BITMAPFILEHEADER; 

typedef struct tagBITMAPINFOHEADER { 
	double biSize; 
	long biWidth; 
	long biHeight; 
	int biPlanes; 
	int biBitCount;
	double biCompression; 
	double biSizeImage; 
	long biXPelsPerMeter; 
	long biYPelsPerMeter; 
	double biClrUsed; 
	double biClrImportant; 
} BITMAPINFOHEADER;