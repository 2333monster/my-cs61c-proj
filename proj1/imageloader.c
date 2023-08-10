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
	FILE *imagefile = fopen(filename,"r");
	if(imagefile == NULL){
		printf("fail to open %s\n", filename);
		return NULL;
	}
	char format[3];
	int maxcolor;
	fscanf(imagefile,"%s",format);
	if(format[0] != 'P' || format[1] != '3'){
		printf("%s wrong format\n", filename);
		return NULL;
	}
	Image *img = (Image*)malloc(sizeof(Image));
	fscanf(imagefile,"%d",&img->cols);
	fscanf(imagefile,"%d",&img->rows);
	fscanf(imagefile,"%d",&maxcolor);
	if(img->rows <0 || img->cols <0 || maxcolor != 255){
		printf("%s wrong format\n", filename);
	}
	int totpixel = img->rows * img->cols;
	img->image = (Color **)malloc(totpixel*sizeof(Color*));
	for(int i=0; i<totpixel;i++){
		*(img->image+i) = (Color*)malloc(sizeof(Color));
		Color* pixel = *(img->image +i);
		fscanf(imagefile,"%hhu %hhu %hhu", &pixel->R,&pixel->G,&pixel->B);
	}
	fclose(imagefile);
	return img;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	printf("P3\n%d %d\n255\n",image->cols,image->rows);
	Color** p = image->image;
	for(int i = 0;i < image->rows;i++){
		for(int j = 0; j < image->cols; j++){
			printf("%3u %3u %3u\n", (*p)->R,(*p)->G,(*p)->B);
			p++;
		}
		printf("%3u %3u %3u\n", (*p)->R,(*p)->G,(*p)->B);
		p++;
	}
	printf("finish");
}

void writeData_in_file(Image *image){
	FILE *fpWrite = fopen("data.txt","w");
	if(fpWrite == NULL){
		printf("no date.txt file");
	}
	fprintf(fpWrite,"P3\n%d %d\n255\n",image->cols,image->rows);
	Color** p = image->image;
	for(int i = 0;i < image->rows;i++){
		for(int j = 0; j < image->cols; j++){
			fprintf(fpWrite,"%3u %3u %3u   ", (*p)->R,(*p)->G,(*p)->B);
			p++;
		}
		fprintf(fpWrite,"\n");
		fprintf(fpWrite,"%3u %3u %3u   ", (*p)->R,(*p)->G,(*p)->B);
		p++;
	}
	fclose(fpWrite);
}
//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	int totpixels = (image->rows)*(image->cols);
	for(int i = 0; i < totpixels; i++){
		free(*(image->image+i));
	}
	free(image-> image);
	free(image);
}

// int main(){
// 	char *file = "D:/fa20-proj1-starter-master/studentOutputs/secretMessage.ppm";
// 	Image *readIn;
// 	readIn = readData(file);
// 	writeData(readIn);
// 	freeImage(readIn);
// }

// int main(int argc, char** argv){
// 	if (argc != 2){
// 		printf("usage: %s <colorfile> \n", argv[0]);
// 	}
// 	Image *readIn;
// 	readIn = readData(argv[1]);
// 	writeData(readIn);
// 	freeImage(readIn);
// }
