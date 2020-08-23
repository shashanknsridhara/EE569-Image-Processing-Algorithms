
// Name: Shashank Nelamangala Sridhara
// USC ID Number: 2082227554
// USC Email: nelamang@usc.edu
// Submission Date: 03/03/2020


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include<bits/stdc++.h>
#include <map>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
    int WIDTH = 512;
	int HEIGHT = 512;	
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
	unsigned char Imagedata[HEIGHT][WIDTH][3];
    unsigned char warpedImage[HEIGHT][WIDTH][3];
	unsigned char reconstructedImage[HEIGHT][WIDTH][3];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), HEIGHT*WIDTH*3, file);
    fclose(file);


	//Forward mapping with Inverse address mapping
	for (unsigned int row = 0; row< HEIGHT; row++){
        for (unsigned int col= 0; col< WIDTH;col++){
			//converting the original indices to cartesian coordinate system
			float xk = 1+col-0.5;
			float yk = HEIGHT + 0.5 -row;
			//Bring to origin and normalize
			float xk_norm =  (xk-255.5)/255.5;
			float yk_norm = (yk-255.5)/255.5;
			//cout<<xk<<": "<<yk<<endl;
			//Applying transformation (reverse address mapping)
			float p_norm = (xk_norm/(sqrt(1 - (pow(yk_norm,2)/2))))*255.5;
			float q_norm = (yk_norm/(sqrt(1 - (pow(xk_norm,2)/2))))*255.5;
			//cout<<p<<": "<<q<<endl;
			//convert back from cartesian to image coordinates
			float p = (p_norm+255.5);
			float q = (q_norm+255.5);
			//cout<<p<<": "<<q<<endl;
			float r = HEIGHT + 0.5 -q;
			float c = p + 0.5-1;
			//cout<<r<<": "<<c<<endl;
			//Interpolation
			int m = floor(r);
			int n = floor(c);
			//cout<<m<<": "<<n<<endl;
			if(m < 0 || n< 0){
				warpedImage[row][col][0] = 0;
				warpedImage[row][col][1] = 0;
				warpedImage[row][col][2] = 0;
			}

			else if(m > 511 || n> 511){
				warpedImage[row][col][0] = 0;
				warpedImage[row][col][1] = 0;
				warpedImage[row][col][2] = 0;
			}
			
			else{
				int pixelR = (Imagedata[m][n][0] + Imagedata[m][n+1][0] + Imagedata[m+1][n][0] + Imagedata[m+1][n+1][0])/4;
				warpedImage[row][col][0] = pixelR;

				int pixelG = (Imagedata[m][n][1] + Imagedata[m][n+1][1] + Imagedata[m+1][n][1] + Imagedata[m+1][n+1][1])/4;
				warpedImage[row][col][1] = pixelG;

				int pixelB = (Imagedata[m][n][2] + Imagedata[m][n+1][2] + Imagedata[m+1][n][2] + Imagedata[m+1][n+1][2])/4;
				warpedImage[row][col][2] = pixelB;
			}
		
			//cout<<"====="<<endl;
		}
    }

	//Inverse Transformation
	for (unsigned int row = 0; row< HEIGHT; row++){
            for (unsigned int col= 0; col< WIDTH;col++){
			
			
			//converting the original indices to cartesian coordinate system
			float xk = 1+col-0.5;
			float yk = HEIGHT + 0.5 -row;

			//Bring to origin and normalize
			float xk_norm =  (xk-255.5)/255.5;
			float yk_norm = (yk-255.5)/255.5;


			//cout<<xk<<": "<<yk<<endl;
			//Applying transformation (reverse address mapping)
			float p_norm = (xk_norm*(sqrt(1 - (pow(yk_norm,2)/2))))*255.5;
			float q_norm = (yk_norm*(sqrt(1 - (pow(xk_norm,2)/2))))*255.5;
			//cout<<p<<": "<<q<<endl;
			//convert back from cartesian to image coordinates

			float p = (p_norm+255.5);
			float q = (q_norm+255.5);
			//cout<<p<<": "<<q<<endl;

			float r = HEIGHT + 0.5 -q;
			float c = p + 0.5 -1;
			//cout<<r<<": "<<c<<endl;
			//Interpolation
			int m = floor(r);
			int n = floor(c);
			//cout<<m<<": "<<n<<endl;
			if(m < 0 || n< 0){
				reconstructedImage[row][col][0] = 0;
				reconstructedImage[row][col][1] = 0;
				reconstructedImage[row][col][2] = 0;
			}

			else if(m > 511 || n> 511){
				reconstructedImage[row][col][0] = 0;
				reconstructedImage[row][col][1] = 0;
				reconstructedImage[row][col][2] = 0;
			}
			
			else{
				int pixelR = (warpedImage[m][n][0] + warpedImage[m][n+1][0] + warpedImage[m+1][n][0] + warpedImage[m+1][n+1][0])/4;
				reconstructedImage[row][col][0] = pixelR;

				int pixelG = (warpedImage[m][n][1] + warpedImage[m][n+1][1] + warpedImage[m+1][n][1] + warpedImage[m+1][n+1][1])/4;
				reconstructedImage[row][col][1] = pixelG;

				int pixelB = (warpedImage[m][n][2] + warpedImage[m][n+1][2] + warpedImage[m+1][n][2] + warpedImage[m+1][n+1][2])/4;
				reconstructedImage[row][col][2] = pixelB;
			}
		
			//cout<<"====="<<endl;
		}
    }

     // Writing Image
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(warpedImage, sizeof(unsigned char), HEIGHT*WIDTH*3, file);
	fclose(file);

	  // Writing Reconstructed Image
	if (!(file=fopen(argv[3],"wb"))) {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(reconstructedImage, sizeof(unsigned char), HEIGHT*WIDTH*3, file);
	fclose(file);
}