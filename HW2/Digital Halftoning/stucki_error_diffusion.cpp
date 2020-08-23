// Name: Shashank Nelamangala Sridhara
// USC ID Number: 2082227554
// USC Email: nelamang@usc.edu
// Submission Date: 02/16/2020


#include <stdio.h>
#include <iostream>
#include <stdlib.h>


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

    //Padding the image
    unsigned char PaddedImage[4+HEIGHT][4+WIDTH][1];
    for(int i=0;i<HEIGHT+4; i++){
        for(int j=0;j<WIDTH+4;j++){
            PaddedImage[i][j][0]=0;
        }
    }
	for(int i=0; i<HEIGHT; i++){
        for(int j=0; j< WIDTH; j++){
            PaddedImage[i+2][j+2][0] = Imagedata[i][j][0];
        }
	}
    //Padding ended

    float Image[HEIGHT+4][WIDTH+4];
    for(int row=0;row<HEIGHT+4;row++){
        for(int col=0;col<WIDTH+4; col++){
            Image[row][col] = PaddedImage[row][col][0];
        }
    }

    unsigned char StuckiErrorDiffusion[HEIGHT][WIDTH][1];
    float Threshold = 128;
    float err;
    int row = 2;
    int col=2;
    while(true){
        if(row%2==0){

            if(Image[row][col]<=128){
                StuckiErrorDiffusion[row-2][col-2][0] = 0;
            }
            else{
                StuckiErrorDiffusion[row-2][col-2][0]=255;
            }
            //Diffusing the error
            err = Image[row][col] - StuckiErrorDiffusion[row-2][col-2][0];
            Image[row][col+1]+= err*(8/42.0);
            Image[row][col+2]+= err*(4/42.0);

            Image[row+1][col-2]+= err*(2/42.0);
            Image[row+1][col-1]+=err*(4/42.0);
            Image[row+1][col]+=err*(8/42.0);
            Image[row+1][col+1]+=err*(4/42.0);
            Image[row+1][col+2]+=err*(2/42.0);

            Image[row+2][col-2]+=err*(1/42.0);
            Image[row+2][col-1]+=err*(2/42.0);
            Image[row+2][col]+=err*(4/42.0);
            Image[row+2][col+1]+=err*(2/42.0);
            Image[row+2][col+2]+=err*(1/42.0);

            if(col==WIDTH-1){
                row=row+1;
            }
            else{
                col+=1;
            }
    }
    else if(row%2!=0){
        if(Image[row][col]<=128){
            StuckiErrorDiffusion[row][col][0] = 0;
        }
        else{
            StuckiErrorDiffusion[row][col][0]=255;
        }
        //Diffusing the error
        err = Image[row][col] - StuckiErrorDiffusion[row][col][0];
        Image[row][col-1]+= err*(8/42.0);
        Image[row][col-2]+= err*(4/42.0);

        Image[row+1][col-2]+= err*(2/42.0);
        Image[row+1][col-1]+=err*(4/42.0);
        Image[row+1][col]+=err*(8/42.0);
        Image[row+1][col+1]+=err*(4/42.0);
        Image[row+1][col+2]+=err*(2/42.0);

        Image[row+2][col-2]+=err*(1/42.0);
        Image[row+2][col-1]+=err*(2/42.0);
        Image[row+2][col]+=err*(4/42.0);
        Image[row+2][col+1]+=err*(2/42.0);
        Image[row+2][col+2]+=err*(1/42.0);

        if(col==0){
            row+=1;
        }
       else{
            col-=1;
        }
    }
       
    if( col== WIDTH-1 && row==HEIGHT-1){
        break;
    }
}
    
    // Writing Error Diffusion image
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(StuckiErrorDiffusion, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	fclose(file);
}