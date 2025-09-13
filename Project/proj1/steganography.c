/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color * pixel = (Color *)malloc(sizeof(Color));
	*pixel = image->image[row][col];
	return pixel;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image *img = (Image *) malloc(sizeof(Image));
	img->rows = image->rows;
	img->cols = image->cols;
	
	img->image = (Color **) malloc(sizeof(Color*) * img->rows);
	for(int i = 0; i<img->rows; i++){
		img->image[i] = (Color *) malloc(sizeof(Color) * img->cols);
	}

	for(int row = 0; row < img->rows; row++){
		for(int col = 0; col < img->cols; col++){
			Color *pixel = evaluateOnePixel(image, row, col);
			uint8_t val = ((pixel->B & (u_int8_t)0x01) == 1) ? (u_int8_t) 255: (u_int8_t) 0;
			img->image[row][col].R = val;
			img->image[row][col].G = val;
			img->image[row][col].B = val;
			free(pixel);
		}
	}
	return img;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc <= 1) exit(-1);
	Image *ori_image = readData(argv[1]);
	if (ori_image == NULL) exit(-1);
	
	Image *output_image = steganography(ori_image);

	writeData(output_image);

	freeImage(ori_image);
	freeImage(output_image);
	return 0;
}
