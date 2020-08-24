function averageEnergy = convolution_test(filter, Image)
    padSize = 132;
    imgSize = 128;
    %Boundary Extension of the Image
    paddedImage= zeros(padSize, padSize);
    for row = 1:imgSize
        for col = 1:imgSize
            paddedImage(row+2, col+2)= Image(row, col);
        end
    end
    
    convolutedImage= zeros(imgSize,imgSize);
    %Convolution
     for row = 3:padSize-2
         for col = 3:padSize-2
             convolution = 0;
             weightSum = 0;
             for i = -2:2
                 for j = -2:2
                     pixel = paddedImage(row+i, col+j);
                     convolution = convolution + (pixel*filter(i+3, j+3));
                     weightSum = weightSum + filter(i+3, j+3);
                 end                
             end
             convolutedImage(row-2, col-2) = convolution;
         end
     end
     
     %finding energy (absolute value)
     sum = 0;
     for row = 1:imgSize
         for col = 1:imgSize
            sum =  sum + abs(convolutedImage(row, col));
         end
     end
     averageEnergy = (sum/(128*128));
end