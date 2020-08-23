// Name: Shashank Nelamangala Sridhara
// USC ID Number: 2082227554
// USC Email: nelamang@usc.edu
// Submission Date: 01/28/2020


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
    int Size_row = 320;
	int Size_col = 320;	
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
	unsigned char OriginalImage[Size_row][Size_col][1];
    if(argc==4){
        
        if (!(file=fopen(argv[3],"rb"))) {
		cout << "Cannot open file: " << argv[3] <<endl;
		exit(1);
	}
	fread(OriginalImage, sizeof(unsigned char), Size_row*Size_col*1, file);
	fclose(file);
    }
	// else {
	// 	BytesPerPixel = atoi(argv[3]);
	// 	// Check if size is specified
	// 	if (argc >= 5){
	// 		Size = atoi(argv[4]);
	// 	}
	// }
	// Allocate image data array
	unsigned char Imagedata[Size_row][Size_col][1];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size_row*Size_col*1, file);
	fclose(file);


    //Denoising-Low pass filtering (mean)

    //Filter Size
    int N = 3;
    int mask[N][N];
    for (unsigned int i=0; i<N;i++){
        for(unsigned int j=0;j<N;j++){
            mask[i][j]=1;
            cout<<mask[i][j]<<" ";
        }
        cout<<endl;
    }
    float weight=N*N;

    unsigned char denoisedImage[Size_row][Size_col][1];

    for (unsigned int row=1; row<Size_row-1; row++){
    	for (unsigned int col=1; col<Size_col-1; col++){
        	float convolution = 0;

            for (int i = -1; i<=1; i++){
                for(int j = -1; j<=1; j++){
                        float pixel = (float)Imagedata[row+i][col+j][0];
                        convolution += pixel*mask[i+1][j+1];                      
                    }
                }
                denoisedImage[row][col][0] = (unsigned char)(convolution/weight);
        }
    }

    //PSNR Calculation
    float MAX = 255;
    float meanSquareError;
	float error = 0.0;
	float normalisingCoeff = Size_row*Size_col;
    for(unsigned int i = 1; i<Size_row-1; i++){
        for(unsigned int j=1; j<Size_col-1;j++){
			error+= pow((denoisedImage[i][j][0] - OriginalImage[i][j][0]),2);
        }
    }
	meanSquareError = error/normalisingCoeff;

    float ratio = (MAX*MAX)/meanSquareError;
    float psnr_db = 10*log10(ratio);
	cout<<"PSNR in DB - Linear filter with uniform mask: "<<psnr_db<<"dB"<<endl;

	// Write image data (filename specified by second argument) from image data matrix
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(denoisedImage, sizeof(unsigned char), Size_row*Size_col*1, file);
	fclose(file);

	return 0;
    
}



