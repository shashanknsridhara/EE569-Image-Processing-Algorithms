
// Name: Shashank Nelamangala Sridhara
// USC ID Number: 2082227554
// USC Email: nelamang@usc.edu
// Submission Date: 02/16/2020


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
    int WIDTH = 481;
	int HEIGHT = 321;	
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

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), HEIGHT*WIDTH*3, file);
	fclose(file);

   //Sobel filter for edge detection Edge detection
   	unsigned char RGB2Gray[HEIGHT][WIDTH][1];
   	
    //For calculation
	float xGradient[HEIGHT][WIDTH][1];
	float yGradient[HEIGHT][WIDTH][1];

    //For visualization
	unsigned char xGradient_normalized[HEIGHT][WIDTH][1];
	unsigned char yGradient_normalized[HEIGHT][WIDTH][1];

    //For calculation
	float GradientMag[HEIGHT][WIDTH][1];

    //For visualization
	unsigned char GradientMag_normalized[HEIGHT][WIDTH][1];

	//For calculation
	float GradientOrient[HEIGHT][WIDTH][1];

	//For visualization
	unsigned char GradientOrient_Normalized[HEIGHT][WIDTH][1];


	//Step1 RGB to gray conversion
	for (unsigned int row=0; row<HEIGHT; row++){
        for (unsigned int col=0; col<WIDTH; col++){
			int R = (int)Imagedata[row][col][0];
			int G = (int)Imagedata[row][col][1];
			int B = (int)Imagedata[row][col][2];

			float Gray = 0.2989*R + 0.5870*G + 0.1140*B;

			RGB2Gray[row][col][0] = (unsigned char)Gray;
		}
	}
	// Writing Grayscale image
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(RGB2Gray, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	fclose(file);

	//Step2 Find Gradient in X and Y Direction
	int grad_x[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
	int grad_y[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
	
	
	for (unsigned int row=1; row<HEIGHT-1; row++){
        for (unsigned int col=1; col<WIDTH-1; col++){

			float Gx = 0;
			float Gy = 0; 
			for (int i = -1; i<=1; i++){
                for(int j = -1; j<=1; j++){
					int pixel = (int)RGB2Gray[row+i][col+j][0];
					Gx += pixel*grad_x[i+1][j+1];
					Gy += pixel*grad_y[i+1][j+1]; 
				}
			}
			xGradient[row][col][0] = Gx;
			yGradient[row][col][0] = Gy;		
		}
	}

    //Step3 Find Gradient Magnitude
	for (unsigned int row=1; row<HEIGHT-1; row++){
        for (unsigned int col=1; col<WIDTH-1; col++){
			float Gx_square = pow(xGradient[row][col][0],2);
			float Gy_square = pow(yGradient[row][col][0],2);
			GradientMag[row][col][0] = sqrt(Gx_square + Gy_square);
			GradientOrient[row][col][0] = atan((yGradient[row][col][0])/(xGradient[row][col][0]));
		}
	}

    //Visualization codes.


	//To find maximum and minimum value in X and Y gradient
	float x_max = 5;
	float x_min =5;
	float y_max = 5;
	float y_min = 5;
	
	for (unsigned int row=1; row<HEIGHT-1; row++){
        for (unsigned int col=0; col<WIDTH-1; col++){
			float x_pixel = xGradient[row][col][0];
			float y_pixel = yGradient[row][col][0];

			if(x_pixel < x_min){
				x_min = x_pixel;
			}
			else if(x_pixel > x_max){
				x_max = x_pixel;
			}

			if(y_pixel < y_min){
				y_min = y_pixel;
			}
			else if(y_pixel > y_max){
				y_max = y_pixel;
			}
			
		}
	}
	cout<<x_min<<" "<<x_max<<" "<<y_max<<" "<<y_min;

	//code to normalize x and y gradient.
	for (unsigned int row=1; row<HEIGHT-1; row++){
        for (unsigned int col=1; col<WIDTH-1; col++){
			float x = xGradient[row][col][0];
			float y = yGradient[row][col][0];
			float x_normalized = ((x - x_min)/(x_max - x_min))*255;
			float y_normalized = ((y - y_min)/(y_max - y_min))*255;
			xGradient_normalized[row][col][0] = (unsigned char) x_normalized;
			yGradient_normalized[row][col][0] = (unsigned char) y_normalized;
			}
	}
	// Writing xGradient image
	if (!(file=fopen(argv[3],"wb"))) {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(xGradient_normalized, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	fclose(file);

	// Writing yGradient image
	if (!(file=fopen(argv[4],"wb"))) {
		cout << "Cannot open file: " << argv[4] << endl;
		exit(1);
	}
	fwrite(yGradient_normalized, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	fclose(file);

	//Normalizing Gradient Magnitude for visualization
	//Calculate Min and Max values
	float Grad_max = 5;
	float Grad_min =5;

	float GradOrient_max = 5;
	float GradOrient_min = 5;
	
	for (unsigned int row=1; row<HEIGHT-1; row++){
        for (unsigned int col=0; col<WIDTH-1; col++){
			float grad_pixel = GradientMag[row][col][0];

			float gradOrientPixel = GradientOrient[row][col][0];

			if(grad_pixel < Grad_min){
				Grad_min = grad_pixel;
			}
			else if(grad_pixel > Grad_max){
				Grad_max = grad_pixel;
			}

			if(gradOrientPixel < GradOrient_min){
				GradOrient_min = gradOrientPixel;
			}
			else if(gradOrientPixel > GradOrient_max){
				GradOrient_max = gradOrientPixel;
			}	
		}
	}
	//Code to Normalize Gradient Magnitude
	for (unsigned int row=1; row<HEIGHT-1; row++){
        for (unsigned int col=1; col<WIDTH-1; col++){
			float grad = GradientMag[row][col][0];
			float gradOr = GradientOrient[row][col][0];

			float grad_normalized = ((grad - Grad_min)/(Grad_max - Grad_min))*255;

			float grad_orient_normalized = ((gradOr - GradOrient_min)/(GradOrient_max - GradOrient_min))*255;
			GradientMag_normalized[row][col][0] = (unsigned char) grad_normalized;
			GradientOrient_Normalized[row][col][0] = (unsigned char) grad_orient_normalized;
			}
	}


	// Gradient Magnitude
	if (!(file=fopen(argv[5],"wb"))) {
		cout << "Cannot open file: " << argv[5] << endl;
		exit(1);
	}
	fwrite(GradientMag_normalized, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	fclose(file);


	// Writing Gradient Orientation image
	// if (!(file=fopen(argv[6],"wb"))) {
	// 	cout << "Cannot open file: " << argv[6] << endl;
	// 	exit(1);
	// }
	// fwrite(GradientOrient_Normalized, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	// fclose(file);
	//return 0;




	//Generating Edge maps based on cumulative distribution.
	cout<<"Histogram"<<endl;
	int histogram[256] = {0};
	float cumulativeHistogram[256];
	for(int i=1; i<HEIGHT-1;i++){
		for(int j=1;j<WIDTH-1; j++){
			histogram[GradientMag_normalized[i][j][0]]+=1;
			//cout<<histogram[GradientMag_normalized[i][j][0]]<<" "<<endl;
		}
		//cout<<endl;
	}
	cumulativeHistogram[0] = histogram[0];
	for (int i=1; i<256;i++){
		cumulativeHistogram[i] = cumulativeHistogram[i-1]+histogram[i];
		
	}
	cout<<"Cumulative"<<endl;
	for (int i=0;i<256;i++){
		cumulativeHistogram[i]/=(float) cumulativeHistogram[255];
		cout<<cumulativeHistogram[i]<<endl;
	}

	//Setting Threshold
	int threshold;
	float upperLimit=0.90;
	for (int k = 0; k<256; k++){
		//cout<<cumulativeHistogram[k]<<endl;
		if(cumulativeHistogram[k]>=upperLimit){
			cout<<k<<endl;
			threshold=k;
			break;
		}
	}
	//cout<<" Threshold"<<threshold<<endl;
	unsigned char EdgeMap[HEIGHT][WIDTH][1];
	//Writing Edge map 
	for (int row=1; row<HEIGHT-1;row++){
		for (int col=1; col<WIDTH-1;col++){
			int pixel = (int)GradientMag_normalized[row][col][0];
			if(pixel>=threshold){
				EdgeMap[row][col][0] = 0;
			}
			else{
				EdgeMap[row][col][0]=255;
			}
		}
	}
	//Writing Edge Map
	if (!(file=fopen(argv[6],"wb"))) {
		cout << "Cannot open file: " << argv[6] << endl;
		exit(1);
	}
	fwrite(EdgeMap, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	fclose(file);

	return 0;
}