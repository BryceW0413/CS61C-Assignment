/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE

	uint16_t dead = rule & 0x1FF;
	uint16_t alive = (rule >> 9) & 0xFFE;
	// Get the rules in two situations

	Color * result = (Color *) malloc(sizeof(Color));
	result->R = 0;
	result->G = 0;
	result->B = 0;
	// Initialize the result

	// Whole calculation process on one single bit at the R bitplane, then repeat
	// this process to other bit planes (G, B)
	for(int bit = 0; bit < 8; bit++){
		int count = 0; // count for alive neighbours

		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				int sample_row = (row - 1 + i)%image->rows;
				int sample_col = (col - 1 + j)%image->cols;
				// Calculate the sample row in circle

				if(!((sample_row == row) && (sample_col == col))){
					if (image->image[sample_row][sample_col].R & (1 << bit)){
						count++;
					}
				}
				// Check numbers of alive neighbors
			}
		}

		int state = image->image[row][col].R & (1 << bit);
		if(state != 0){
			if((alive & (1 << count)) != 0){
				result->R += (1 << bit);
			} 
		}else if((dead & (1 << count)) != 0){
			result->R += (1 << bit);
		}
		// Determine the next state based on current state
	}
 

	// Operations on G bitplane
	for(int bit = 0; bit < 8; bit++){
		int count = 0; // count for alive neighbours

		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				int sample_row = (row - 1 + i)%image->rows;
				int sample_col = (col - 1 + j)%image->cols;
				// Calculate the sample row in circle

				if(!((sample_row == row) && (sample_col == col))){
					if (image->image[sample_row][sample_col].G & (1 << bit)){
						count++;
					}
				}
				// Check numbers of alive neighbors
			}
		}

		int state = image->image[row][col].G & (1 << bit);

		if(state != 0){
			if((alive & (1 << count)) != 0){
				result->G += (1 << bit);
			} 
		}else if((dead & (1 << count)) != 0){
			result->G += (1 << bit);
		}
		// Determine the next state based on current state
	}

	// Operations on B plane
	for(int bit = 0; bit < 8; bit++){
		int count = 0; // count for alive neighbours

		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				int sample_row = (row - 1 + i)%image->rows;
				int sample_col = (col - 1 + j)%image->cols;
				// Calculate the sample row in circle

				if(!((sample_row == row) && (sample_col == col))){
					if (image->image[sample_row][sample_col].B & (1 << bit)){
						count++;
					}
				}
				// Check numbers of alive neighbors
			}
		}

		int state = image->image[row][col].B & (1 << bit);
		if(state != 0){
			if((alive & (1 << count)) != 0){
				result->B += (1 << bit);
			} 
		}else if((dead & (1 << count)) != 0){
			result->B += (1 << bit);
		}
		// Determine the next state based on current state
	}

	return result;	
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
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
			Color *pixel = evaluateOneCell(image, row, col, rule);
			img->image[row][col] = *pixel;
			free(pixel);
		}
	}
	return img;
}
/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	char *filename = argv[1];
	char *endptr;

	uint32_t rule = strtol(argv[2], &endptr, 0);
	if(*endptr != '\0') exit(-1); // Make sure the rule is correctly conerted to intgers

	Image *ori_image = readData(filename); // Read the original image
	if(ori_image == NULL) exit(-1);

	Image *next_image = life(ori_image, rule); // Process the image and get the next state
	
	writeData(next_image);

	freeImage(ori_image);
	freeImage(next_image);
	return 0;
}
