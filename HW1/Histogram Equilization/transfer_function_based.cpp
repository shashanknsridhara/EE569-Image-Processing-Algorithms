// Name: Shashank Nelamangala Sridhara
// USC ID Number: 2082227554
// USC Email: nelamang@usc.edu
// Submission Date: 01/28/2020


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <map>
#include<cmath>
using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
    int WIDTH = 560;
	int HEIGHT = 400;	
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

   //Transfer Based Histogram Equilisation

    //Output image declaration
    unsigned char enhancedImage[HEIGHT][WIDTH][3];
    
    //1D array for each channels
    int redPixels[HEIGHT*WIDTH];
    int greenPixels[HEIGHT*WIDTH];
    int bluePixels[HEIGHT*WIDTH];

    //Filling the channels to array
    int arrItr = 0;
    for(unsigned int i =0; i<HEIGHT;i++){
        for (unsigned int j = 0; j<WIDTH; j++){
			
            //out<<i<<":"<<j<<endl;
            redPixels[arrItr] = (int)Imagedata[i][j][0];
            greenPixels[arrItr] = (int)Imagedata[i][j][1];
            bluePixels[arrItr] = (int)Imagedata[i][j][2];
			arrItr++;
        }
    }

    //Writing to csv file to plot Original Histogram of the Toy Image
    // std::fstream original_hist;
    // original_hist.open("original_hist.csv", ios::out);
	// cout<<"2"<<endl;
    // for(unsigned int k=0;k<HEIGHT*WIDTH;k++){
		
    //     original_hist<<redPixels[k]<<", "
    //             <<greenPixels[k]<<", "
    //             <<bluePixels[k]<<"\n";

    // }

	//Counting the number of pixels for histogram
	map<int, int> hashMapR;
	map<int, int> hashMapG;
	map<int, int> hashMapB;
	for (unsigned int l=0; l<HEIGHT*WIDTH;l++){
		
		if(hashMapR.find(redPixels[l])!=hashMapR.end()){
			hashMapR[redPixels[l]]++;
		}
		else{
			hashMapR.insert(pair<int,int>(redPixels[l],1));
		}
		if(hashMapG.find(greenPixels[l])!=hashMapG.end()){
			hashMapG[greenPixels[l]]++;
		}
		else{
			hashMapG.insert(pair<int,int>(greenPixels[l],1));
		}

		if(hashMapB.find(bluePixels[l])!=hashMapB.end()){
			hashMapB[bluePixels[l]]++;
		}
		else{
			hashMapB.insert(pair<int,int>(bluePixels[l],1));
		}
	}

	int xRPixels[256];
	double yRCounts[256];

	int xGPixels[256];
	double yGCounts[256];

	int xBPixels[256];
	double yBCounts[256];



	map<int, int>::iterator itr; 
	int r = 0;
    for (itr = hashMapR.begin(); itr != hashMapR.end(); ++itr) { 
        //cout<< "RED"<<endl;
		xRPixels[r] = itr->first;
		yRCounts[r] = (float)(itr->second)/(HEIGHT*WIDTH);
		// cout << '\t' << xRPixels[r]
        //      << '\t' << yRCounts[r] << '\n';
		r++;
		
    }
	int g =0;
	for (itr = hashMapG.begin(); itr != hashMapG.end(); ++itr) { 
        //cout<< "GREEN"<<endl; 
		xGPixels[g] = itr->first;
		yGCounts[g] = (float)(itr->second)/(HEIGHT*WIDTH);
		// cout << '\t' << xGPixels[g]
        //      << '\t' << yGCounts[g] << '\n';
		g++;
		
    }
	int b=0;
	for (itr = hashMapB.begin(); itr != hashMapB.end(); ++itr) { 
        //cout<< "BLUE"<<endl; 
		xBPixels[b] = itr->first;
		yBCounts[b] = (float)(itr->second)/(HEIGHT*WIDTH);

		// cout << '\t' << xBPixels[b]
        //      << '\t' << yBCounts[b] << '\n';
		b++;
    }  
    //cout << endl;


	//Writing to csv file
    std::fstream originalCDF;
    originalCDF.open("originalCDF.csv", ios::out);
    for(unsigned int k=0;k<256;k++){
		
        originalCDF<<yRCounts[k]<<", "
                <<yGCounts[k]<<", "
                <<yBCounts[k]<<"\n";

    }

	double rCumulative[256];
	double gCumulative[256];
	double bCumulative[256];

	rCumulative[0] = yRCounts[0];
	gCumulative[0] = yGCounts[0];
	bCumulative[0] = yBCounts[0];
	//intitialize the cumulative distribution
	for(unsigned int m = 1; m<256;m++){
		rCumulative[m]=yRCounts[m]+rCumulative[m-1];
		gCumulative[m]=yGCounts[m]+gCumulative[m-1];
		bCumulative[m]=yBCounts[m]+bCumulative[m-1];
		
		// cout <<rCumulative[m]<<"\t";
		// cout <<gCumulative[m]<<"\t";
		// cout <<bCumulative[m]<<"\t";

		// cout<<endl;
	}

	//rounding off
	for(unsigned int n = 0; n<256;n++){
		rCumulative[n]= floor(rCumulative[n]*255);
		gCumulative[n]=	floor(gCumulative[n]*255);
		bCumulative[n]=	floor(bCumulative[n]*255);
		// cout <<xRPixels[n]<<":"<<rCumulative[n]<<"\t";
		// cout <<xGPixels[n]<<":"<<gCumulative[n]<<"\t";
		// cout <<xBPixels[n]<<":"<<bCumulative[n]<<"\t";
		//cout<<endl;
	}

	//To plot the transfer function of the output
	std::fstream transfer_func_cumulative;
    transfer_func_cumulative.open("transfer_func_cumulative.csv", ios::out);
    for(unsigned int k=0;k<256;k++){
		
        transfer_func_cumulative<<rCumulative[k]<<", "
                <<gCumulative[k]<<", "
                <<bCumulative[k]<<"\n";
    }


	int rOutput[HEIGHT*WIDTH];
	int gOutput[HEIGHT*WIDTH];
	int bOutput[HEIGHT*WIDTH];


	//Mapping back
	int finalItr=0;
	for(unsigned int i =0; i<HEIGHT;i++){
        for (unsigned int j = 0; j<WIDTH; j++){
			int pixR = Imagedata[i][j][0];
			int pixG = Imagedata[i][j][1];
			int pixB = Imagedata[i][j][2];

			enhancedImage[i][j][0] = rCumulative[pixR];
			enhancedImage[i][j][1] = gCumulative[pixG];
			enhancedImage[i][j][2] = bCumulative[pixB];

			rOutput[finalItr]= (int) enhancedImage[i][j][0];
			gOutput[finalItr]= (int) enhancedImage[i][j][1];
			bOutput[finalItr]= (int) enhancedImage[i][j][2];
			finalItr++;
		}
	}


//	Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(enhancedImage, sizeof(unsigned char), HEIGHT*WIDTH*3, file);
	fclose(file);

	return 0;
    
}



