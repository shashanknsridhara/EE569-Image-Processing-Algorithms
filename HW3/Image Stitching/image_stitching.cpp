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
#include<sys/resource.h>

using namespace std;

int main(int argc, char *argv[])

{

	//To increase Stack size
	const rlim_t kStackSize = 24*1024*1024;
	struct rlimit rl;
	rl.rlim_cur = kStackSize;
	setrlimit(RLIMIT_STACK, &rl);




	// Define file pointer and variables
	FILE *file;

	int WIDTH_I = 480;
	int HEIGHT_I = 720;

    int WIDTH_C = 2000;
	int HEIGHT_C = 1500;	
	int BytesPerPixel;
    int Size = 256;

	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	//Given Images (Left, Right, Middle)
	unsigned char MiddleImage[HEIGHT_I][WIDTH_I][3];
	unsigned char LeftImage[HEIGHT_I][WIDTH_I][3];
	unsigned char RightImage[HEIGHT_I][WIDTH_I][3];

	// Read Left image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(LeftImage, sizeof(unsigned char), HEIGHT_I*WIDTH_I*3, file);
    fclose(file);


	// Read Right image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[2],"rb"))) {
		cout << "Cannot open file: " << argv[2] <<endl;
		exit(1);
	}
	fread(RightImage, sizeof(unsigned char), HEIGHT_I*WIDTH_I*3, file);
    fclose(file);

	// Read Middle image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[3],"rb"))) {
		cout << "Cannot open file: " << argv[3] <<endl;
		exit(1);
	}
	fread(MiddleImage, sizeof(unsigned char), HEIGHT_I*WIDTH_I*3, file);
    fclose(file);

	//Declaring Canvas
	unsigned char Canvas[HEIGHT_C][WIDTH_C][3];
	unsigned char StitchedImage[HEIGHT_C][WIDTH_C][3];
	float H_L[3][3] = {{-30.8975,  0.267510394,  1553.27437},{-8.60849818 -2.54597342,  2101.15424},{-0.0161620692,  0.000864037213,  1.00000000}};
	//Writing Left Image on Canvas
	for(unsigned int row = 0; row<HEIGHT_I; row++){
		for(unsigned int col = 0; col<WIDTH_I; col++){
			Canvas[row+391][col][0] = LeftImage[row][col][0];
			Canvas[row+391][col][1] = LeftImage[row][col][1];
			Canvas[row+391][col][2] = LeftImage[row][col][2];
		}
	}
    
	//Writing Middle Image on Canvas
	for(unsigned int row = 0; row<HEIGHT_I; row++){
		for(unsigned int col = 0; col<WIDTH_I; col++){
			Canvas[row+391][WIDTH_I+281+col][0] = MiddleImage[row][col][0];
			Canvas[row+391][WIDTH_I+281+col][1] = MiddleImage[row][col][1];
			Canvas[row+391][WIDTH_I+281+col][2] = MiddleImage[row][col][2];
		}
	}

	//Writing Right Image on Canvas
	for(unsigned int row = 0; row<HEIGHT_I; row++){
		for(unsigned int col = 0; col<WIDTH_I; col++){
			Canvas[row+391][(2*WIDTH_I)+561+col][0] = RightImage[row][col][0];
			Canvas[row+391][(2*WIDTH_I)+561+col][1] = RightImage[row][col][1];
			Canvas[row+391][(2*WIDTH_I)+561+col][2] = RightImage[row][col][2];
		}
	}

	//Projecting Left Image
	for(unsigned int row = 0; row<HEIGHT_I; row++){
		for(unsigned int col = 0; col<WIDTH_I; col++){
			cout<<row<<":"<<col<<endl;
			float xl = 1+col-0.5;
			float yl = 750 + 0.5 -row;
			cout<<xl<<":"<<yl<<endl;

			float xl_trans = H_L[0][0]*xl + H_L[0][1]*yl + H_L[0][2];
			float yl_trans = H_L[1][0]*xl + H_L[1][1]*yl + H_L[1][2];
			float wl = H_L[2][0]*xl + H_L[2][1]*yl + H_L[2][2];

			float x2 = (xl_trans/wl);
			float y2 =(yl_trans/wl);
			cout<<x2<<":"<<y2<<endl;

			float row_img = 750 +0.5 -1;
			float col_img = x2+0.5-1; 
			cout<<row_img<<":"<<col_img<<endl;

			int k = floor(row_img);
			int l = floor(col_img);
			cout<<k<<":"<<l<<endl;
			int m = k+391;
			int n = l;
			cout<<m<<":"<<n<<endl;
			//cout<<m<<": "<<n<<endl;
			// if(m < 0 || n< 0){
			// 	StitchedImage[][][0] = 0;
			// 	StitchedImage[rc][cc][1] = 0;
			// 	StitchedImage[rc][cc][2] = 0;
			// }

			// else if(m > 1500 || n> 2000){
			// 	StitchedImage[rc][cc][0] = 0;
			// 	StitchedImage[rc][cc][1] = 0;
			// 	StitchedImage[rc][cc][2] = 0;
			// }
			
			// else{
				int pixelR = (LeftImage[k][l][0] + LeftImage[k][l+1][0] + LeftImage[k+1][l][0] + LeftImage[k+1][l+1][0])/4;
				StitchedImage[m][n][0] = pixelR;

				int pixelG = (LeftImage[k][l][1] + LeftImage[k][l+1][1] + LeftImage[k+1][l][1] + LeftImage[k+1][l+1][1])/4;
				StitchedImage[m][n][1] = pixelG;

				int pixelB = (LeftImage[k][l][2] + LeftImage[k][l+1][2] + LeftImage[k+1][l][2] + LeftImage[k+1][l+1][2])/4;
				StitchedImage[m][n][2] = pixelB;
			// }
		
		}
		cout<<"=============="<<endl;
	}


     // Writing Image
	if (!(file=fopen(argv[4],"wb"))) {
		cout << "Cannot open file: " << argv[4] << endl;
		exit(1);
	}
	fwrite(Canvas, sizeof(unsigned char), HEIGHT_C*WIDTH_C*3, file);
	fclose(file);


     // Writing Image
	if (!(file=fopen(argv[5],"wb"))) {
		cout << "Cannot open file: " << argv[5] << endl;
		exit(1);
	}
	fwrite(StitchedImage, sizeof(unsigned char), HEIGHT_C*WIDTH_C*3, file);
	fclose(file);
}