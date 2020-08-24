
% Name: Shashank Nelamangala Sridhara
% USC ID Number: 2082227554
% USC Email: nelamang@usc.edu
% Submission Date: 03/22/2020

function convolutedImage = convolution_seg(filter, Image)
    convolutedImage= zeros(450,600);
    %Convolution
     for row = 8:464-7
         for col = 8:614-7
             convolution = 0;
             for i = -2:2
                 for j = -2:2
                     pixel = Image(row+i, col+j);
                     convolution = convolution + (pixel*filter(i+3, j+3));
                 end                
             end
             convolutedImage(row-7, col-7) = convolution;
         end
     end
end