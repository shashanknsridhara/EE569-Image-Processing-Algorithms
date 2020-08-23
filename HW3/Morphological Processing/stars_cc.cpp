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
#include <fstream>

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
	unsigned char Imagedata[HEIGHT][WIDTH][1];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
    fclose(file);

   
    //Pad the image
    unsigned int PaddedImage[2+HEIGHT][2+WIDTH][1];
    for(int i=0;i<HEIGHT+2; i++){
        for(int j=0;j<WIDTH+2;j++){
            PaddedImage[i][j][0]=0;
        }
    }
	for(int i=0; i<HEIGHT; i++){
        for(int j=0; j< WIDTH; j++){
            PaddedImage[i+1][j+1][0] = Imagedata[i][j][0];
        }
	}    

    //Thresholding
    for(int i=1; i<HEIGHT+2; i++){
        for(int j=1; j< WIDTH+2; j++){
            if(PaddedImage[i][j][0] > 128){
                PaddedImage[i][j][0]= 1;
            }
            else{
                PaddedImage[i][j][0] =0;
            }
        }
    }

    //First Parse
    map<int, int> matchTable;
    int objLabel = 1;
    for (unsigned int row = 1; row<HEIGHT+1; row++){
        for (unsigned int col=1; col<WIDTH+1; col++){
            int neighbor_array[4]={0,0,0,0};
            if (PaddedImage[row][col][0]== 1){
                neighbor_array[0] = PaddedImage[row][col-1][0];
                neighbor_array[1] = PaddedImage[row-1][col-1][0];
                neighbor_array[2] = PaddedImage[row-1][col][0];
                neighbor_array[3] = PaddedImage[row-1][col+1][0];

                if(neighbor_array[0]==0 && neighbor_array[1]==0 && neighbor_array[2]==0 && neighbor_array[3]==0){
                    PaddedImage[row][col][0] = objLabel;
                    objLabel++;
                }
                else{

                   //To find minimum value
                   int min;
                   //initializing min
                   for(int k =0; k<4; k++){
                       if(neighbor_array[k]!=0){
                           min=neighbor_array[k];
                           break;
                       }
                   }
                   //Finding minimum value in the array
                   for(int k = 0; k<4;k++){
                       if(neighbor_array[k]!=0){
                           if(neighbor_array[k] < min){
                               min = neighbor_array[k];
                           }
                       }
                   }

                   //mapping in hash table
                   for(int k = 0; k<4; k++){
                       if(neighbor_array[k]>min){
                           if(matchTable.find(neighbor_array[k])!=matchTable.end()){
			                    matchTable[neighbor_array[k]] = min;
		                    }
		                    else{
			                    matchTable.insert(pair<int,int>(neighbor_array[k],min));
		                    }
                        }
                   }
                    PaddedImage[row][col][0] = min;

                }
            }
        }
    }
    
    cout<<matchTable[2]<<endl;
    //2nd Parse
    for(unsigned int row =1; row<HEIGHT+1; row++){
        for(unsigned int col=1; col<WIDTH+1; col++){
            if(matchTable.find(PaddedImage[row][col][0])!=matchTable.end()){
                PaddedImage[row][col][0] = matchTable[PaddedImage[row][col][0]];
            }
        }
    }

    //calculate the number of stars
    map <int, int>numberOfStars;
    for(unsigned int row =0; row<HEIGHT; row++){
        for(unsigned int col=0; col<WIDTH; col++){
            if(numberOfStars.find(PaddedImage[row][col][0]) == numberOfStars.end()){
                numberOfStars.insert(pair<int,int>(PaddedImage[row][col][0],1));
            }
            else{
                numberOfStars[PaddedImage[row][col][0]]++;
            }
        }
    }
    cout<<"Number of Stars: "<<numberOfStars.size()<<endl;

    std::fstream SizeOfStars;
    SizeOfStars.open("SizeOfStars.csv", ios::out);
    for(int k=1; k<=114; k++){
        SizeOfStars<<k<<", "<<numberOfStars[k]<<"\n";
    }


    if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(PaddedImage, sizeof(unsigned char), HEIGHT*WIDTH*1, file);
	fclose(file);
}