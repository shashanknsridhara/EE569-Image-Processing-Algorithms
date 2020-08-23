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

    unsigned char dithering[HEIGHT][WIDTH][1];


    
    //Dithering Implementation

    //Step 1: Generation of Index matrix
    int I_b[2][2] = {{1,2},{3,0}};
    int N = 4;
	//To create I4
	int I4[N][N];

	for(int i = 0;i<N;i++){
		for (int j = 0; j<N;j++){
			int val = 4*I_b[i%(N/2)][j%(N/2)];
			if(i<(N/2) && j<(N/2)){
				I4[i][j] = val+1;
			}
			else if(i<(N/2) && j>=(N/2)){
				I4[i][j] = val +2;
			}

			else if(i>=(N/2) && j<(N/2)){
				I4[i][j] = val +3;
			}


			else if(i>=(N/2) && j>=(N/2)){
				I4[i][j] = val;
			}
		cout<<I4[i][j]<<" ";
		}
		cout<<endl;
	}
cout<<"==================="<<endl;
	//To create I8
	int M = 8;
	int I8[8][8];
	for(int i = 0;i<M;i++){
		for (int j = 0; j<M;j++){
			int val = 4*I4[i%(M/2)][j%(M/2)];
			if(i<(M/2) && j<(M/2)){
				I8[i][j] = val+1;
			}
			else if(i<(M/2) && j>=(M/2)){
				I8[i][j] = val +2;
			}

			else if(i>=(M/2) && j<(M/2)){
				I8[i][j] = val +3;
			}


			else if(i>=(M/2) && j>=(M/2)){
				I8[i][j] = val;
			}
		cout<<I8[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"==================="<<endl;
	//To create I16

	int P = 16;
	int I16[P][P];
	for(int i = 0;i<P;i++){
		for (int j = 0; j<P;j++){
			int val = 4*I8[i%(P/2)][j%(P/2)];
			if(i<(P/2) && j<(P/2)){
				I16[i][j] = val+1;
			}
			else if(i<(P/2) && j>=(P/2)){
				I16[i][j] = val +2;
			}

			else if(i>=(P/2) && j<(P/2)){
				I16[i][j] = val +3;
			}


			else if(i>=(P/2) && j>=(P/2)){
				I16[i][j] = val;
			}
		cout<<I16[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"==================="<<endl;

	//To create I32
	int Q = 32;
	int I32[Q][Q];
	for(int i = 0;i<Q;i++){
		for (int j = 0; j<Q;j++){
			int val = 4*I16[i%(Q/2)][j%(Q/2)];
			if(i<(Q/2) && j<(Q/2)){
				I32[i][j] = val+1;
			}
			else if(i<(Q/2) && j>=(Q/2)){
				I32[i][j] = val +2;
			}

			else if(i>=(Q/2) && j<(Q/2)){
				I32[i][j] = val +3;
			}


			else if(i>=(Q/2) && j>=(Q/2)){
				I32[i][j] = val;
			}
		cout<<I32[i][j]<<" ";
		}
		cout<<endl;
	}
    cout<<"======================"<<endl;
	//Generating Threshold matrix
	//2*2 Threshold matrix
	int Th2[2][2];
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			Th2[i][j] = ((I_b[i][j]+0.5)/(2*2))*255;
			cout<<Th2[i][j]<<" ";
		}
		cout<<endl;
	}
    cout<<"======================"<<endl;

	//8*8 Threshold matrix
	int Th8[8][8];
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			Th8[i][j] = ((I8[i][j]+0.5)/(8*8))*255;
			cout<<Th8[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"======================"<<endl;

	//32*32 Threshold matrix
	int Th32[32][32];
	for(int i=0;i<32;i++){
		for(int j=0;j<32;j++){
			Th32[i][j] = ((I32[i][j]+0.5)/(32*32))*255;
			cout<<Th32[i][j]<<" ";
		}
		cout<<endl;
	}
	unsigned char Dithering2[HEIGHT][WIDTH][1];
	unsigned char Dithering8[HEIGHT][WIDTH][1];
	unsigned char Dithering32[HEIGHT][WIDTH][1];
	//Dithering Output for 2*2 Threshold matrix
    for (unsigned int row=0; row<HEIGHT; row++){
        for (unsigned int col=0; col<WIDTH; col++){
			//Dithering output for 2*2
            if(Imagedata[row][col][0]<= Th2[row%2][col%2]){
				Dithering2[row][col][0] = 0;
			}
			else if(Imagedata[row][col][0]> Th2[row%2][col%2]){
				Dithering2[row][col][0] = 255;
			}

			//Dithering output for 8*8
			if(Imagedata[row][col][0]<= Th8[row%8][col%8]){
				Dithering8[row][col][0] = 0;
			}
			else if(Imagedata[row][col][0]> Th8[row%8][col%8]){
				Dithering8[row][col][0] = 255;
			}

			//Dithering output for 32*32
			if(Imagedata[row][col][0]<= Th32[row%32][col%32]){
				Dithering32[row][col][0] = 0;
			}
			else if(Imagedata[row][col][0]> Th32[row%32][col%32]){
				Dithering32[row][col][0] = 255;
			}
			
        }
    }

    // Writing Dithering 2 image
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Dithering2, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	fclose(file);


    // Writing Dithering 8 image
	if (!(file=fopen(argv[3],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Dithering8, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	fclose(file);


    // Writing Dithering 32 image
	if (!(file=fopen(argv[4],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Dithering32, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	fclose(file);
}