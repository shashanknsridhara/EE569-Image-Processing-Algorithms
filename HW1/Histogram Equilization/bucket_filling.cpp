
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <map>
#include<cmath>

using namespace std;


// void BubbleSort(int arr[], int SIZE){
//     cout<<"Inside function"<<endl;
// 	bool isSwapped;
// 	int i,j;
//     for(i = 0; i<SIZE-1; i++){
//         isSwapped = false;
//         for(j=0; i<SIZE-i-1;j++){
//             if(arr[j] > arr[j+1]){
//                 int memSpace = arr[j];
//                 arr[j] = arr[j+1];
//                 arr[j+1] = memSpace;

//                 isSwapped = true;
//             }
//         }
//         if(isSwapped==false){
//             break;
//         }
//     }
// }

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
    unsigned char bucketListEnhancedImage[HEIGHT][WIDTH][3];
    
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


	// std::sort(redPixels,redPixels+(HEIGHT*WIDTH));
	// std::sort(greenPixels,greenPixels+(HEIGHT*WIDTH));
	// std::sort(bluePixels,bluePixels+(HEIGHT*WIDTH));


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
		yRCounts[r] = itr->second;
		// cout << '\t' << xRPixels[r]
        //      << '\t' << yRCounts[r] << '\n';
		r++;
		
    }
	int g =0;
	for (itr = hashMapG.begin(); itr != hashMapG.end(); ++itr) { 
        //cout<< "GREEN"<<endl; 
		xGPixels[g] = itr->first;
		yGCounts[g] = itr->second;
		// cout << '\t' << xGPixels[g]
        //      << '\t' << yGCounts[g] << '\n';
		g++;
		
    }
	int b=0;
	for (itr = hashMapB.begin(); itr != hashMapB.end(); ++itr) { 
        //cout<< "BLUE"<<endl; 
		xBPixels[b] = itr->first;
		yBCounts[b] = itr->second;

		// cout << '\t' << xBPixels[b]
        //      << '\t' << yBCounts[b] << '\n';
		b++;
    }  
    //cout << endl;

	int rCumulative[256];
	int gCumulative[256];
	int bCumulative[256];

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

	std::fstream csv_bucket;
    csv_bucket.open("original_cdf_bucket.csv", ios::out);
    for(unsigned int k=0;k<256;k++){
		
        csv_bucket<<rCumulative[k]<<", "
                <<gCumulative[k]<<", "
                <<bCumulative[k]<<"\n";
    }

	
	int pixelsPerBucket = floor((HEIGHT*WIDTH)/(256));
	cout<<"PixelsPerBucket: "<<pixelsPerBucket<<endl;

	int rPixelCount[256];
	int gPixelCount[256];
	int bPixelCount[256];

	//Initialising the count array
	for(int k = 0; k< 256;k++){
		rPixelCount[k]=0;
		gPixelCount[k]=0;
		bPixelCount[k]=0;
	}

	int rOutput[HEIGHT*WIDTH];
	int gOutput[HEIGHT*WIDTH];
	int bOutput[HEIGHT*WIDTH];

	int finalItr = 0;

	//Iterate through the Image
	for (int i=0; i< HEIGHT;i++){
		for(int j=0; j< WIDTH;j++){
			int rPixel = (int) Imagedata[i][j][0];
			int gPixel = (int) Imagedata[i][j][1];
			int bPixel = (int) Imagedata[i][j][2];

			//To find the #cnt occurance of r,g,b values in the sorted array

			

			int indexR = rCumulative[rPixel-1];
			int indexG= gCumulative[gPixel-1];
			int indexB = bCumulative[bPixel-1];
		//cout<<rPixel<<":"<<(indexR+ rPixelCount[rPixel])/(pixelsPerBucket)<<"\t|";
		rOutput[finalItr]= (int) (indexR+ rPixelCount[rPixel])/(pixelsPerBucket);
		gOutput[finalItr]= (int) (indexG+ gPixelCount[gPixel])/(pixelsPerBucket);
		bOutput[finalItr]= (int) (indexB+ bPixelCount[bPixel])/(pixelsPerBucket);
		bucketListEnhancedImage[i][j][0] =(indexR + rPixelCount[rPixel])/(pixelsPerBucket);
		bucketListEnhancedImage[i][j][1] =(indexG + gPixelCount[gPixel])/(pixelsPerBucket);
		bucketListEnhancedImage[i][j][2] =(indexB + bPixelCount[bPixel])/(pixelsPerBucket);
		
		rPixelCount[rPixel]++;
		gPixelCount[gPixel]++;
		bPixelCount[bPixel]++;
		finalItr++;
		}
	} 
	
	//Remove before submitting
	map<int, int> hashMapRout;
	map<int, int> hashMapGout;
	map<int, int> hashMapBout;
	for (unsigned int l=0; l<HEIGHT*WIDTH;l++){
		
		if(hashMapR.find(rOutput[l])!=hashMapRout.end()){
			hashMapRout[rOutput[l]]++;
		}
		else{
			hashMapRout.insert(pair<int,int>(rOutput[l],1));
		}
		if(hashMapGout.find(gOutput[l])!=hashMapGout.end()){
			hashMapGout[gOutput[l]]++;
		}
		else{
			hashMapGout.insert(pair<int,int>(gOutput[l],1));
		}

		if(hashMapBout.find(bOutput[l])!=hashMapBout.end()){
			hashMapBout[bOutput[l]]++;
		}
		else{
			hashMapBout.insert(pair<int,int>(bOutput[l],1));
		}
	}

	int xRPixelsOut[256];
	int yRCountsOut[256];

	int xGPixelsOut[256];
	int yGCountsOut[256];

	int xBPixelsOut[256];
	int yBCountsOut[256];



	map<int, int>::iterator itr_o; 
	int r_o = 0;
    for (itr_o = hashMapRout.begin(); itr_o != hashMapRout.end(); ++itr_o) { 
        //cout<< "RED"<<endl;
		xRPixelsOut[r_o] = itr_o->first;
		yRCountsOut[r_o] = (float) itr_o->second;
		// cout << '\t' << xRPixels[r]
        //      << '\t' << yRCounts[r] << '\n';
		r_o++;
		
    }
	int g_o=0;
	for (itr_o = hashMapGout.begin(); itr_o != hashMapGout.end(); ++itr_o) { 
        //cout<< "GREEN"<<endl; 
		xGPixelsOut[g_o] = itr_o->first;
		yGCountsOut[g_o] = itr_o->second;
		// cout << '\t' << xGPixels[g]
        //      << '\t' << yGCounts[g] << '\n';
		g_o++;
		
    }
	int b_o=0;
	for (itr_o = hashMapBout.begin(); itr_o != hashMapBout.end(); ++itr_o) { 
        //cout<< "BLUE"<<endl; 
		xBPixelsOut[b_o] = itr_o->first;
		yBCountsOut[b_o] = itr_o->second;

		// cout << '\t' << xBPixels[b]
        //      << '\t' << yBCounts[b] << '\n';
		b_o++;
    }  
    //cout << endl;


	//Writing to csv file
    std::fstream outputCDF_bucket;
    outputCDF_bucket.open("outputCDF_bucket.csv", ios::out);
    for(unsigned int k=0;k<256;k++){
		
        outputCDF_bucket<<yRCountsOut[k]<<", "
                <<yGCountsOut[k]<<", "
                <<yBCountsOut[k]<<"\n";

    }


	std::fstream final_rgb;
    final_rgb.open("output_hist_bucket.csv", ios::out);
    for(unsigned int k=0;k<HEIGHT*WIDTH;k++){
		
        final_rgb<<rOutput[k]<<", "
                <<gOutput[k]<<", "
                <<bOutput[k]<<"\n";
    }
//	Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(bucketListEnhancedImage, sizeof(unsigned char), HEIGHT*WIDTH*3, file);
	fclose(file);

	return 0;
    
}



