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
    float Image[HEIGHT][WIDTH];
    for(int row=0;row<HEIGHT;row++){
        for(int col=0;col<WIDTH; col++){
        Image[row][col] = Imagedata[row][col][0];
        }
    }

    unsigned char FSDithering[HEIGHT][WIDTH][1];
    float Threshold = 65;
    float err;
    int row = 0;
    int col=0;
    while(true){

        if(row%2==0){

            if(Image[row][col]<=128){
                FSDithering[row][col][0] = 0;
            }
            else{
                FSDithering[row][col][0]=255;
            }
            //Diffusing the error
            err = Image[row][col] - FSDithering[row][col][0];

            if(col == 0){
                Image[row][col+1]+= err*(7/16.0);
                Image[row+1][col]+=  err*(5/16.0);
                Image[row+1][col+1]+= err*(1/16.0);
            }

            else if(col == WIDTH-1){
                Image[row+1][col-1]+= err*(3/16.0);
                Image[row+1][col]+=  err*(5/16.0);
            }
            else if(row ==HEIGHT-1){
                Image[row][col+1]+= err*(7/16.0);
               
            }
            else{
                Image[row][col+1]+= err*(7/16.0);
                Image[row+1][col-1]+= err*(3/16.0);
                Image[row+1][col]+= err*(5/16.0);
                Image[row+1][col+1]+=err*(1/16.0);
            }
        if(col==WIDTH-1){
            row=row+1;
        }
        else{
            col+=1;
        }
    }
    else if(row%2!=0){
        if(Image[row][col]<=128){
            FSDithering[row][col][0] = 0;
        }
        else{
            FSDithering[row][col][0]=255;
        }
        //Diffusing the error
        err = Image[row][col] - FSDithering[row][col][0];

        if(col == 0){
            Image[row+1][col+1]+= err*(3/16.0);
            Image[row+1][col]+=  err*(5/16.0);
         }

        else if(col == WIDTH-1){
            Image[row][col-1]+=  err*(7/16.0);
            Image[row+1][col-1]+= err*(1/16.0);
            Image[row+1][col]+=  err*(5/16.0);
        }
        else if(row ==HEIGHT-1){;
            Image[row][col-1]+= err*(7/16.0);
        }
        else{
            Image[row][col-1]+= err*(7/16.0);
            Image[row+1][col-1]+= err*(1/16.0);
            Image[row+1][col]+= err*(5/16.0);
            Image[row+1][col+1]+=err*(3/16.0);
        }
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
	fwrite(FSDithering, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	fclose(file);
}