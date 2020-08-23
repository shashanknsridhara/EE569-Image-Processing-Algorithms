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


    //MHC Demosaicing

    //filter parameters definition
    float filter1[5][5] = {{0,0,-1,0,0},{0,0,2,0,0},{-1,2,4,2,-1},{0, 0, 2, 0, 0},{0, 0, -1, 0, 0}};
    float filter2[5][5] = {{0,0,-3/2,0,0},{0,2,0,2,0},{-3/2,0,6,0,-3/2},{0, 2, 0, 2, 0},{0, 0, -3/2, 0, 0}};
    float filter3[5][5] = {{0,0,1/2,0,0}, {0,-1,0,-1,0}, {-1,4,5,4,-1},{0,-1,0,-1,0},{0,0,1/2,0,0}};
    float filter4[5][5] = {{0,0,-1,0,0},{0,-1,4,-1,0},{1/2,0,5,0,1/2},{0,-1,4,-1,0},{0,0,-1,0,0}};
    float weight = 8.0;

    //Output image declaration
    unsigned char newImage[HEIGHT][WIDTH][3];

    //input image padding
    //pass
    for (unsigned int row=2; row<HEIGHT-2; ++row){
        for (unsigned int col=2; col<WIDTH-2; ++col){
            
            //If Green
            if((row%2 == 0 && col%2 ==0) || (row%2 != 0 && col%2 != 0)){
                float convolutionR = 0;
                float convolutionB = 0;

                for (int i = -2; i<=2; ++i){
                    for(int j = -2; j<=2; ++j){
                        float pixel = Imagedata[row+i][col+j][0];
                        if(row%2 == 0 && col%2 ==0){
                            convolutionR += pixel* filter3[i+2][j+2];
                            convolutionB += pixel* filter4[i+2][j+2];
                        }
                        if(row%2 != 0 && col%2 != 0){
                            convolutionR += pixel* filter4[i+2][j+2];
                            convolutionB += pixel*filter3[i+2][j+2];
                        } 
                    }
                }
            //To wrap the values
            float redValueAtG = (convolutionR/weight);
            float blueValueAtG = (convolutionB/weight);
                if(redValueAtG < 0){
                    redValueAtG = 0;
                }
                if(redValueAtG >255){
                    redValueAtG = 255;
                }
                if(blueValueAtG >255){
                    blueValueAtG = 255;
                }
                
                if(blueValueAtG < 0){
                    blueValueAtG=0;
                }
        
                newImage[row][col][0] = (unsigned char)redValueAtG;
                newImage[row][col][1] = Imagedata[row][col][0];
                newImage[row][col][2] = (unsigned char)blueValueAtG;

            }
            
            //If Red
            else if(row%2 == 0 && col%2 !=0){
                float convolutionG = 0;
                float convolutionB = 0;

                for (int i = -2; i<=2; ++i){
                    for(int j = -2; j<=2; ++j){
                        float pixel = Imagedata[row+i][col+j][0];
                        convolutionG += pixel* filter1[i+2][j+2];
                        convolutionB += pixel* filter2[i+2][j+2];
                    }
                }
            float greenValueAtR = (convolutionG/weight);
            float blueValueAtR = (convolutionB/weight);
                if(greenValueAtR < 0){
                    greenValueAtR = 0;
                }
                if(greenValueAtR > 255){
                    greenValueAtR = 255;
                }
                if(blueValueAtR >255){
                    blueValueAtR = 255;
                }
                
                if(blueValueAtR < 0){
                    blueValueAtR=0;
                }
        
                newImage[row][col][0] = Imagedata[row][col][0];
                newImage[row][col][1] = (unsigned char)greenValueAtR;
                newImage[row][col][2] = (unsigned char)blueValueAtR;
            }

            //If Blue
            else if(row%2 != 0 && col%2 == 0){
                float convolutionG = 0;
                float convolutionR = 0;
                for (int i = -2; i<=2; ++i){
                    for(int j = -2; j<=2; ++j){
                        float pixel = Imagedata[row+i][col+j][0];
                        convolutionG += pixel* filter2[i+2][j+2];
                        convolutionR += pixel* filter1[i+2][j+2];
                    }
                }
            float greenValueAtBlue = (convolutionG/weight);
            float redValueAtBlue = (convolutionR/weight);
                if(greenValueAtBlue < 0){
                    greenValueAtBlue = 0;
                }
                if(greenValueAtBlue >255){
                    greenValueAtBlue = 255;
                }
                if(redValueAtBlue >255){
                    redValueAtBlue = 255;
                }
                
                if(redValueAtBlue < 0){
                    redValueAtBlue=0;
                }

                newImage[row][col][0] = (unsigned char)redValueAtBlue;
                newImage[row][col][1] = (unsigned char)greenValueAtBlue;
                newImage[row][col][2] = Imagedata[row][col][0];
            }

        }
    }


	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(newImage, sizeof(unsigned char), HEIGHT*WIDTH*3, file);
	fclose(file);

	return 0;
    
}



