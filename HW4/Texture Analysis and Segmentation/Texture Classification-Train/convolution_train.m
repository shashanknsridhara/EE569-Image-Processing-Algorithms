
% Name: Shashank Nelamangala Sridhara
% USC ID Number: 2082227554
% USC Email: nelamang@usc.edu
% Submission Date: 03/22/2020

function featureMatrix = ApplyLawsFilters_train(filterBank, TrainingImages)
    featureMatrix = zeros(9,25);
    for imgs = 1:9
       Image = TrainingImages(:,:,imgs);
       for f = 1:25
           filter = filterBank(:,:,f);
           averageEnergy = convolution_train(filter, Image);
           featureMatrix(imgs, f) = averageEnergy;
       end
    end
end

function averageEnergy = convolution_train(filter, Image)
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