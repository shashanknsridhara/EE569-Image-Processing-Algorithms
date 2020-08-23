// Name: Shashank Nelamangala Sridhara
// USC ID Number: 2082227554
// USC Email: nelamang@usc.edu
// Submission Date: 02/16/2020


#include <stdio.h>
#include <iostream>
#include <stdlib.h>



using namespace std;
int MBVQ(float, float, float);
int CMYW (string, float, float, float);
int MYGC (string, float, float, float);
int RGMY (string, float, float, float);
int KRGB (string, float, float, float);
int RGBM (string, float, float, float);
int CMGB (string, float, float, float);



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
    unsigned char MBVQImage[HEIGHT][WIDTH][3];

	//Creating an Image copy in float
    float Image[HEIGHT][WIDTH][3];
    for(int row=0;row<HEIGHT;row++){
        for(int col=0;col<WIDTH; col++){
        Image[row][col][0] = Imagedata[row][col][0];
        Image[row][col][1] = Imagedata[row][col][1];
        Image[row][col][2] = Imagedata[row][col][2];
        }
    }
	//Flags
	//CMYQW-> 1, MYGC -> 2, RGMY -> 3, KRGB -> 4, RGBM -> 5, CMGB -> 6
	string cmyw = "CMYW";
	string mygc = "MYGC";
	string rgmy = "RGMY";
	string krgb = "KRGB";
	string rgbm = "RGBM";
	string cmgb = "CMGB";
	for (unsigned int row=0; row<HEIGHT;row++){
		for (unsigned int col = 0; col<WIDTH; col++){
			//Determine MBVQ
			float R = Image[row][col][0];
			float G = Image[row][col][1];
			float B =  Image[row][col][2];
			int mbvq = MBVQ(R, G,B);
			int v;
			switch(mbvq){
				case 1: v = CMYW(cmyw, R, G, B);
						break;
				case 2: v = MYGC(mygc, R, G, B);
						break;
				case 3: v = RGMY(rgmy, R, G, B);
						break;
				case 4: v =  KRGB(krgb, R, G, B);
						break;
				case 5: v = RGBM(rgbm, R, G, B);
						break;
				case 6: v = CMGB(cmgb, R, G, B);
						break;
			}
			
		switch(v){
			case 1: MBVQImage[row][col][0] = 255;
					MBVQImage[row][col][1] = 255;
					MBVQImage[row][col][2] = 255;
					break;
			case 2: MBVQImage[row][col][0] = 255;
					MBVQImage[row][col][1] = 0;
					MBVQImage[row][col][2] = 0;
					break;
			case 3: MBVQImage[row][col][0] = 0;
					MBVQImage[row][col][1] = 255;
					MBVQImage[row][col][2] = 0;
					break;
			case 4: MBVQImage[row][col][0]=0;
					MBVQImage[row][col][1]=0;
					MBVQImage[row][col][2]=255;
					break;
			case 5: MBVQImage[row][col][0] = 0;
					MBVQImage[row][col][1] = 255;
					MBVQImage[row][col][2] = 255;
					break;
			case 6: MBVQImage[row][col][0] = 255;
					MBVQImage[row][col][1] = 0;
					MBVQImage[row][col][2] = 255;
					break;
			case 7: MBVQImage[row][col][0] = 255;
					MBVQImage[row][col][1] = 255;
					MBVQImage[row][col][2] = 0;
					break;
			case 8: MBVQImage[row][col][0] = 0;
					MBVQImage[row][col][1] = 0;
					MBVQImage[row][col][2] = 0;
					break;
		}
	if(row %2 == 0){
		float err0 = Image[row][col][0] - MBVQImage[row][col][0];
    	float err1 = Image[row][col][1] - MBVQImage[row][col][1];
    	float err2 = Image[row][col][2] - MBVQImage[row][col][2];
            
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
    }
    else if(row%2!=0){
        //Diffusing the error to each channel
        float err0 = Image[row][col][0] - MBVQImage[row][col][0];
        float err1 = Image[row][col][1] - MBVQImage[row][col][1];
        float err2 = Image[row][col][2] - MBVQImage[row][col][2];

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
	}
		
	}
}
    // Writing MBVQ Image image
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(MBVQImage, sizeof(unsigned char), HEIGHT*WIDTH*3, file);
	fclose(file);
}

//To find the vertices
int MBVQ(float R, float G, float B){
	if((R+G)>255){
		if((G+B)>255){
			if((R+G+B)>510){
				return 1;
			}
			else{
				return 2;
			}
		}
		else{
			return 3;
		}
	}
	else{
		if(!((G+B) >255)){
			if(!((R+G+B) > 255)){
				return 4;
			}
			else{
				return 5;
			}
		}
		else{
			return 6;
		}
	}
}

int CMYW(string mbvq, float R, float G, float B){
	int vertex;
	if (mbvq == "CMYW"){
		//White
        vertex = 1;
        if (B < 128){
            if (B <= R){
                if (B <= G){
					//Yellow
                    vertex = 7;
				}	
			}
		}
        if (G < 128){
            if (G <= B){
                if (G <= R){
					//Magenta
                    vertex = 6;
				}
			}
		}
        if (R < 128){
            if (R <= B){
                if (R <= G){
					//Cyan
                    vertex = 5;
				}
			}
		}
	}
	return vertex;

}
int MYGC(string mbvq, float R, float G, float B){
	int vertex;
	   if (mbvq == "MYGC"){
		   //Magenta
        vertex = 6; 
        if (G >= B){
            if (R >= B){
                if (R >= 128){
					//Yellow
                    vertex = 7;
				}
                else{
					//Green
                    vertex = 3;
				}
			}
		}
        if (G >= R){
            if (B >= R){
                if (B >= 128){
					//Cyan
                    vertex = 5; 
				}
                else{
					//Green
                    vertex = 3;
				}
			}
		}
	   }
	   return vertex;
}

int RGMY(string mbvq, float R, float G, float B){
	int vertex;	
	  if (mbvq == "RGMY"){
        if (B > 128){
            if (R > 128){
                if (B >= G){
					//Magenta
                    vertex = 6;
				}
                else{
					//Yellow
                    vertex = 7;
				}
			}
            else{
                if (G > B + R){
					//Green
                    vertex = 3;
				}
                else{ 
					//Magenta
                    vertex = 6;
				}
			}
		}
        else{
            if (R >= 128){
                if (G >= 128){
					//Yellow
                    vertex = 7;
				}
                else{
					//Red
                    vertex = 2;
				}
			}
            else{
                if (R >= G){
					//Red
                    vertex = 2;
				}
				else{
					//Green
                    vertex = 3;
				}
			}
		}
	  }
	  return vertex;
}

int KRGB(string mbvq, float R, float G, float B){
	 int vertex;
	 if (mbvq == "KRGB"){
		 //Black
        vertex = 8;
        if (B > 128){
            if (B >= R){
                if (B >= G){
					//Blue
                    vertex = 4;
				}
			}
		}
        if (G > 128){
            if (G >= B){
                if (G >= R){
					//Green
                    vertex = 3;
				}
			}
		}
        if (R > 128){
            if (R >= B){
                if (R >= G){
					//Red
                    vertex = 2;
				}
			}
		}
	 }
	 return vertex;
}
int RGBM(string mbvq, float R, float G, float B){
	int vertex;
	 if (mbvq == "RGBM"){
        //Green
		vertex = 3;
        if (R > G){
            if (R >= B){
                if (B < 128){
					//Red
                    vertex = 2;
				}
                else{
					//Magenta
                    vertex = 6;
				}
			}
		}
        if (B > G){
            if (B >= R){
                if (R < 128){
					//Blue
                    vertex = 4;
				}
				else{
					//Magenta
                    vertex = 6;
				}
			}
		}
	 }
	 return vertex;
}

int CMGB(string mbvq, float R, float G, float B){
	int vertex;
	if (mbvq == "CMGB"){
        if (B > 128){
            if ( R > 128){
                if (G >= R){
					//Cyan
                    vertex = 5;
				}
                else{
					//Magenta
                    vertex = 6;
				}
			}
            else{
                if (G > 128){
					//cyan
                    vertex = 5;
				}
                else{
					//Blue
                    vertex = 4;
				}
			}
		}
        else{
            if ( R > 128){
                if (R - G + B >= 128){
					//Magenta
                    vertex = 6;
				}
                else{
					//Green
                    vertex = 3;
				}
			}
            else{
                if (G >= B){
					//Green
                    vertex = 3;
				}
                else{
					//Blue
                    vertex = 4;
				}
			}
		}
	}
	return vertex;

}



