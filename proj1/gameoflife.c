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

int ring(int x, int y){
	return (x+y)%y;
}

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	Color* nextState = (Color*) malloc(sizeof(Color));
	int aliveNeighbourR=0, aliveNeighbourG=0,aliveNeighbourB=0;
	int isaliveR,isaliveG,isaliveB;
	int rx[8] = {-1,-1,-1,0,0,1,1,1};
	int cx[8] = {-1,0,1,-1,1,-1,0,1};

	isaliveR = (*(image->image + row * image->cols + col))->R == 255;
	isaliveG = (*(image->image + row * image->cols + col))->G == 255;
	isaliveB = (*(image->image + row * image->cols + col))->B == 255;

	for(int i=0;i<8;i++){
		int new_row = ring(row+rx[i],image->rows);
		int new_col = ring(col+cx[i],image->cols);
		if((*(image->image+new_row*image->cols+new_col))->R == 255){
			aliveNeighbourR++;
		}
		if((*(image->image+new_row*image->cols+new_col))->G == 255){
			aliveNeighbourG++;
		}
		if((*(image->image+new_row*image->cols+new_col))->B == 255){
			aliveNeighbourB++;
		}
	}
	int idR = 9*isaliveR + aliveNeighbourR;
	int idG = 9*isaliveG + aliveNeighbourG;
	int idB = 9*isaliveB + aliveNeighbourB;

	if(rule & (1<<idR)){
		nextState->R = 255;
	}
	else{
		nextState->R = 0;
	}
	if(rule & (1<<idG)){
		nextState->G = 255;
	}
	else{
		nextState->G = 0;
	}
	if(rule & (1<<idB)){
		nextState->B = 255;
	}
	else{
		nextState->B = 0;
	}
	
	return nextState;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image* new = (Image*)malloc(sizeof(Image));
	new->rows = image->rows;
	new->cols = image->cols;
	new->image = (Color**)malloc((new->cols)*(new->rows)*sizeof(Color*));
	Color** p = new->image;
	for(int i = 0; i < new->rows; i++){
		for(int j = 0; j < new->cols; j++){
			*p = evaluateOneCell(image,i,j,rule);
			p++;
		}
	}
	return new;
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
	if(argc != 3){
		printf("usage: %s filename rule\n", argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
    	printf("rule is a hex number beginning with 0x; Life is 0x1808. \n");
    	return 1;
	}
	Image* readIn = readData(argv[1]);
	uint32_t rule = strtol(argv[2],NULL,16);
	Image* nextImage = life(readIn,rule);
	writeData(nextImage);
	freeImage(nextImage);
	freeImage(readIn);
	return 0;
}

// int main()
// {
// 	Image* readIn = readData("D:/fa20-proj1-starter-master/testInputs/GliderGuns.ppm");
// 	uint32_t rule = strtol("0x1808",NULL,16);
// 	Image* nextImage = life(readIn,rule);
// 	writeData_in_file(nextImage);
// 	freeImage(nextImage);
// 	freeImage(readIn);
// 	return 0;
// }

