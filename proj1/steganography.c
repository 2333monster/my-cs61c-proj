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
	Color **p = image->image;
	Color * secret = (Color *)malloc(sizeof(Color));
	p += (col + row*(image->cols));
	int LSB = (*p)->B & 1;
	secret->B = secret->G = secret->R = LSB*255;
	return secret;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image *new = (Image *)malloc(sizeof(Image));
	new->cols = image->cols;
	new->rows = image->rows;
	new->image = (Color **)malloc((new->cols)*(new->rows)*sizeof(Color *));
	Color **p = new->image;
	for (int i = 0; i < new->rows; i++){
		for(int j = 0; j < new->cols; j++){
			*p = evaluateOnePixel(image,i,j);
			p++;
		}
	}
	return new;
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
int 
main()
{
	//YOUR CODE HERE
	// if (argc != 2){
	// 	printf("Usage: %s<colorfile>\n",argv[0] );
	// 	return 1;
	// }
	char* file ="D:/fa20-proj1-starter-master/studentOutputs/secretMessage.ppm";
	Image* img = readData(file);
	Image* steImage = steganography(img);
	writeData(steImage);
	freeImage(steImage);
	freeImage(img);
	return 0;
}
