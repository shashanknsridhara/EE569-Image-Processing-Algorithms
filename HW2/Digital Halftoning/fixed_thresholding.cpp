// Name: Shashank Nelamangala Sridhara
// USC ID Number: 2082227554
// USC Email: nelamang@usc.edu
// Submission Date: 02/16/2020


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
    int WIDTH = 750;
	int HEIGHT = 500;	
	int BytesPerPixel;
    int Size = 256;

	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5){
			Size = atoi(argv[4]);
		}
	}
	// Allocate image data array
	unsigned char Imagedata[HEIGHT][WIDTH][1];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	fclose(file);

    unsigned char fixed_thresholdingImage[HEIGHT][WIDTH][1];

    //Fixed Thresholding Implementation
    int Threshold = 128;
    for (unsigned int row=0; row<HEIGHT; row++){
        for (unsigned int col=0; col<WIDTH; col++){
            int pixel = (int)Imagedata[row][col][0];
            if(pixel < Threshold){
                fixed_thresholdingImage[row][col][0] = (unsigned char)0;
            }
            else if(pixel >= Threshold){
                fixed_thresholdingImage[row][col][0] = (unsigned char)255;
            }
        }
    }

    // Writing Grayscale image
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(fixed_thresholdingImage, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	fclose(file);

}