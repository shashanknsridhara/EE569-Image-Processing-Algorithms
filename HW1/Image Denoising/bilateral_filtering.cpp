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


    //Denoising- Bilateral Filtering
    
	//Filter Size
    int N = 5;
    double bilateral_filter[N][N];
	const double  PI= 3.14159265358979323846;
	double standardDeviation_c = 0.01;
    double standardDeviation_s = 0.1;
	double normalisingCoeff_c = 2*pow(standardDeviation_c,2);
    double normalisingCoeff_s = 2*pow(standardDeviation_s,2); 

	unsigned char bilateralFilteredImage[Size_row][Size_col][1];
   
	for (int i =2; i<Size_row-2;i++){
		for (int j=2; j<Size_col-2;j++){
			double windowWeight = 0.0;
			double sum = 0.0;
			double pixelNr = 0.0;
            //cout<<i<<" :"<<j<<" :"<<endl;
			for (int k = -2; k<=2; k++){
				for(int l= -2; l<=2;l++){
					double numR = (pow(k,2)+ pow(l,2))/normalisingCoeff_c;
					//cout<<"numR :"<<numR<<" || ";
                    double absPixelDiff= abs(Imagedata[i][j][0]-Imagedata[i+k][j+l][0]);
					//cout<<"absPixelDiff :"<<absPixelDiff<<" || ";
                    double pixelDiff = (pow(absPixelDiff,2))/normalisingCoeff_s;
					//cout<<"pixelDiff :"<<pixelDiff<<" || "<<endl;
					windowWeight = exp(-numR-pixelDiff);
                    //cout<<windowWeight<<" ";
					pixelNr += Imagedata[i+k][j+l][0]*windowWeight;
					sum +=windowWeight;
				}
                //cout<<endl;
			}
			bilateralFilteredImage[i][j][0] = (unsigned char) pixelNr/sum;
		}
	}

    //PSNR Calculation
    float MAX = 255;
    float meanSquareError;
	float error = 0.0;
	float coeff = Size_row*Size_col;
    for(unsigned int i = 2; i<Size_row-2; i++){
        for(unsigned int j=2; j<Size_col-2;j++){
			error+= pow((bilateralFilteredImage[i][j][0] - OriginalImage[i][j][0]),2);
        }
    }
	meanSquareError = error/coeff;

    float ratio = (MAX*MAX)/meanSquareError;
    float psnr_db = 10*log10(ratio);
	cout<<"PSNR in DB - Bilateral Filtering: "<<psnr_db<<"dB"<<endl;

	// Write image data (filename specified by second argument) from image data matrix
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(bilateralFilteredImage, sizeof(unsigned char), Size_row*Size_col*1, file);
	fclose(file);

	return 0;
    
}



