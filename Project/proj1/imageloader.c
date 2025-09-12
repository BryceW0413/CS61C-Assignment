/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *file = fopen(filename, "r");
	char magic[3];
	fscanf(file, "%2s", magic);
	if (strcmp(magic, "P3") != 0)
	{
		printf("unsupported format\n");
		fclose(file);
		exit(1);
	}

	int cols, rows, maxColor;
	fscanf(file, "%d %d", &cols, &rows);
	fscanf(file, "%d", &maxColor);

	Image* result = (Image*) malloc(sizeof(Image));
	result->cols = cols;
	result->rows = rows;
	result->image = (Color** )malloc(rows * sizeof(Color *));
	for(int i = 0; i < rows; i++){
		result->image[i] = (Color *) malloc(cols * sizeof(Color));
	}

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			fscanf(file, "%3hhu %3hhu %3hhu", &result->image[i][j].R, &result->image[i][j].G, &result->image[i][j].B);
		}
	}
	fclose(file);
	return result;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	int cols, rows;
	cols = image->cols;
	rows = image->rows;

    printf("P3\n");
    printf("%d %d\n", cols, rows);
    printf("255\n");
	for(int i =0; i<rows; i++){
		for (int j = 0; j < cols; j++){
			printf("%3hhu %3hhu %3hhu", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B); 
			if(j < cols-1){
				printf("   ");
			}
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	    for (int i = 0; i < image->rows; i++) {
        free(image->image[i]);
    }
	free(image->image);
	free(image);
}