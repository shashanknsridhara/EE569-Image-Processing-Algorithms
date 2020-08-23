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
    int WIDTH = 640;
	int HEIGHT = 480;	
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
    
    //Creating an Image copy in float
    float Image[HEIGHT][WIDTH][3];
    for(int row=0;row<HEIGHT;row++){
        for(int col=0;col<WIDTH; col++){
        Image[row][col][0] = Imagedata[row][col][0];
        Image[row][col][1] = Imagedata[row][col][1];
        Image[row][col][2] = Imagedata[row][col][2];
        }
    }

    //Converting Image into CMYK
    for(int row=0;row<HEIGHT;row++){
        for(int col=0;col<WIDTH; col++){
            Image[row][col][0] = 255 - Image[row][col][0];
            Image[row][col][1] = 255 - Image[row][col][1];
            Image[row][col][2] = 255 - Image[row][col][2];
        }
    }
    unsigned char SeperableDiffusion[HEIGHT][WIDTH][3];
    float Threshold = 128;
    float err0, err1,err2;
    int row = 0;
    int col=0;

    while(true){

        if(row%2==0){
            //Quantizing C channel
            if(Image[row][col][0]<=127){
                SeperableDiffusion[row][col][0] = 0;
            }
            else{
                SeperableDiffusion[row][col][0]=255;
            }

            //Quantizing M channel
            if(Image[row][col][1]<=127){
                SeperableDiffusion[row][col][1] = 0;
            }
            else{
                SeperableDiffusion[row][col][1]=255;
            }

            //Quantizing Y channel
            if(Image[row][col][2]<=127){
                SeperableDiffusion[row][col][2] = 0;
            }
            else{
                SeperableDiffusion[row][col][2]=255;
            }
            //Diffusing the error of each channel
            err0 = Image[row][col][0] - SeperableDiffusion[row][col][0];
            err1 = Image[row][col][1] - SeperableDiffusion[row][col][1];
            err2 = Image[row][col][2] - SeperableDiffusion[row][col][2];
            
            if(col == 0){
                Image[row][col+1][0]+= err0*(7/16.0);
                Image[row+1][col][0]+=  err0*(5/16.0);
                Image[row+1][col+1][0]+= err0*(1/16.0);

                Image[row][col+1][1]+= err1*(7/16.0);
                Image[row+1][col][1]+=  err1*(5/16.0);
                Image[row+1][col+1][1]+= err1*(1/16.0);

                Image[row][col+1][2]+= err2*(7/16.0);
                Image[row+1][col][2]+=  err2*(5/16.0);
                Image[row+1][col+1][2]+= err2*(1/16.0);
            }

            else if(col == WIDTH-1){
                Image[row+1][col-1][0]+= err0*(3/16.0);
                Image[row+1][col][0]+=  err0*(5/16.0);

                Image[row+1][col-1][1]+= err1*(3/16.0);
                Image[row+1][col][1]+=  err1*(5/16.0);

                Image[row+1][col-1][2]+= err2*(3/16.0);
                Image[row+1][col][2]+=  err2*(5/16.0);
            }
            else if(row ==HEIGHT-1){
                Image[row][col+1][0]+= err0*(7/16.0);
                Image[row][col+1][1]+= err1*(7/16.0);
                Image[row][col+1][2]+= err2*(7/16.0);               
            }
            else{
                Image[row][col+1][0]+= err0*(7/16.0);
                Image[row+1][col-1][0]+= err0*(3/16.0);
                Image[row+1][col][0]+= err0*(5/16.0);
                Image[row+1][col+1][0]+=err0*(1/16.0);

                Image[row][col+1][1]+= err1*(7/16.0);
                Image[row+1][col-1][1]+= err1*(3/16.0);
                Image[row+1][col][1]+= err1*(5/16.0);
                Image[row+1][col+1][1]+=err1*(1/16.0);

                Image[row][col+1][2]+= err2*(7/16.0);
                Image[row+1][col-1][2]+= err2*(3/16.0);
                Image[row+1][col][2]+= err2*(5/16.0);
                Image[row+1][col+1][2]+=err2*(1/16.0);
            }
        if(col==WIDTH-1){
            row=row+1;
        }
        else{
            col+=1;
        }
    }
    else if(row%2!=0){
        //Quantizing C channel
        if(Image[row][col][0]<=127){
            SeperableDiffusion[row][col][0] = 0;
        }
        else{
            SeperableDiffusion[row][col][0]=255;
        }

        //Quantizing M channel
        if(Image[row][col][1]<=127){
            SeperableDiffusion[row][col][1] = 0;
        }
        else{
            SeperableDiffusion[row][col][1]=255;
        }

        //Quantizing Y channel
        if(Image[row][col][2]<=127){
            SeperableDiffusion[row][col][2] = 0;
        }
        else{
            SeperableDiffusion[row][col][2]=255;
        }

        //Diffusing the error to each channel
        err0 = Image[row][col][0] - SeperableDiffusion[row][col][0];
        err1 = Image[row][col][1] - SeperableDiffusion[row][col][1];
        err2 = Image[row][col][2] - SeperableDiffusion[row][col][2];

        if(col == 0){
            Image[row+1][col+1][0]+= err0*(3/16.0);
            Image[row+1][col][0]+=  err0*(5/16.0);

            Image[row+1][col+1][1]+= err1*(3/16.0);
            Image[row+1][col][1]+=  err1*(5/16.0);

            Image[row+1][col+1][2]+= err2*(3/16.0);
            Image[row+1][col][2]+=  err2*(5/16.0);
         }

        else if(col == WIDTH-1){
            Image[row][col-1][0]+=  err0*(7/16.0);
            Image[row+1][col-1][0]+= err0*(1/16.0);
            Image[row+1][col][0]+=  err0*(5/16.0);


            Image[row][col-1][1]+=  err1*(7/16.0);
            Image[row+1][col-1][1]+= err1*(1/16.0);
            Image[row+1][col][1]+=  err1*(5/16.0);


            Image[row][col-1][2]+=  err2*(7/16.0);
            Image[row+1][col-1][2]+= err2*(1/16.0);
            Image[row+1][col][2]+=  err2*(5/16.0);
        }
        else if(row ==HEIGHT-1){;
            Image[row][col-1][0]+= err0*(7/16.0);
            Image[row][col-1][1]+= err1*(7/16.0);
            Image[row][col-1][2]+= err2*(7/16.0);
        }
        else{
            Image[row][col-1][0]+= err0*(7/16.0);
            Image[row+1][col-1][0]+= err0*(1/16.0);
            Image[row+1][col][0]+= err0*(5/16.0);
            Image[row+1][col+1][0]+=err0*(3/16.0);

            Image[row][col-1][1]+= err1*(7/16.0);
            Image[row+1][col-1][1]+= err1*(1/16.0);
            Image[row+1][col][1]+= err1*(5/16.0);
            Image[row+1][col+1][1]+=err1*(3/16.0);

            Image[row][col-1][2]+= err2*(7/16.0);
            Image[row+1][col-1][2]+= err2*(1/16.0);
            Image[row+1][col][2]+= err2*(5/16.0);
            Image[row+1][col+1][2]+=err2*(3/16.0);
            
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

     //Converting Image back to RGB
    for(int row=0;row<HEIGHT;row++){
        for(int col=0;col<WIDTH; col++){
            SeperableDiffusion[row][col][0] = 255 - SeperableDiffusion[row][col][0];
            SeperableDiffusion[row][col][1] = 255 - SeperableDiffusion[row][col][1];
            SeperableDiffusion[row][col][2] = 255 - SeperableDiffusion[row][col][2];
        }
    }
    // Writing Error Diffusion image
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(SeperableDiffusion, sizeof(unsigned char), HEIGHT*WIDTH*3, file);
	fclose(file);
}