// Name: Shashank Nelamangala Sridhara
// USC ID Number: 2082227554
// USC Email: nelamang@usc.edu
// Submission Date: 01/28/2020
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
    int WIDTH = 600;
	int HEIGHT = 532;	
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
	unsigned char Imagedata[HEIGHT][WIDTH][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), HEIGHT*WIDTH*BytesPerPixel, file);
	fclose(file);

   //Bilinear Demosaicing

    //filter parameters definition
    int Gverfilter[3][3] = {{0, 1, 0}, {0, 0, 0}, {0, 1, 0}};
    int Ghorfilter[3][3] = {{0,0,0}, {1,0,1}, {0,0,0}};
    int R2Gfilter[3][3] = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    int RBfilter[3][3] = {{1,0,1}, {0,0,0}, {1, 0, 1}};
    int weightG = 2;
    int weightRB = 4;

    //Output image declaration
    unsigned char newImage[HEIGHT][WIDTH][3];


    for (unsigned int row=1; row<HEIGHT-1; row++){
        for (unsigned int col=1; col<WIDTH-1; col++){
            //If Green
            if((row%2 == 0 && col%2 ==0) || (row%2 != 0 && col%2 != 0)){
                float convolutionR = 0;
			    float convolutionB = 0;
                //Convolution operation
                for (int i = -1; i<=1; i++){
                    for(int j = -1; j<=1; j++){
                        unsigned char pixel = Imagedata[row+i][col+j][0];
                        if(row%2 != 0 && col%2 !=0){
                            convolutionR += pixel* Gverfilter[1+i][1+j];
                            convolutionB += pixel*Ghorfilter[1+i][1+j];
                        }
                        if(row%2 == 0 && col%2 == 0){
                            convolutionR += pixel* Ghorfilter[1+i][1+j];
                            convolutionB += pixel*Gverfilter[1+i][1+j];
                        }                      
                    }
                }
                newImage[row][col][0] = (unsigned char)(convolutionR/weightG);
                newImage[row][col][1] = Imagedata[row][col][0];
                newImage[row][col][2] = (unsigned char)(convolutionB/weightG);

            }
            //If Red
            else if(row%2 == 0 && col%2 !=0){
                float convolutionG = 0;
			    float convolutionB = 0;
                //Convolution operation
                for (int i = -1; i<=1; i++){
                    for(int j = -1; j<=1; j++){
                        unsigned char pixel = Imagedata[row+i][col+j][0];
                        convolutionG += pixel* R2Gfilter[1+i][1+i];
                        convolutionB += pixel* RBfilter[1+i][1+j];
                    }
                }
                newImage[row][col][0] = Imagedata[row][col][0];
                newImage[row][col][1] = (unsigned char)(convolutionG/weightRB);
                newImage[row][col][2] = (unsigned char)(convolutionB/weightRB);
            }

            //If Blue
            else if(row%2 != 0 && col%2 == 0){
                float convolutionG = 0;
			    float convolutionR = 0;
                //Convolution operation
                for (int i = -1; i<=1; i++){
                    for(int j = -1; j<=1; j++){
                        unsigned char pixel = Imagedata[row+i][col+j][0];
                        convolutionG += pixel* R2Gfilter[1+i][1+j];
                        convolutionR += pixel* RBfilter[1+i][1+j];
                    }
                }
                
                newImage[row][col][0] = (unsigned char)(convolutionR/weightRB);
                newImage[row][col][1] = (unsigned char)(convolutionG/weightRB);
                newImage[row][col][2] = Imagedata[row][col][0];
            }

            }
            
         }

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(newImage, sizeof(unsigned char), HEIGHT*WIDTH*3, file);
	fclose(file);

	return 0;
    
}



