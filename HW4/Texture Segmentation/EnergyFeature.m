
% Name: Shashank Nelamangala Sridhara
% USC ID Number: 2082227554
% USC Email: nelamang@usc.edu
% Submission Date: 03/22/2020

function EnergyMatrix = EnergyFeature(ImageBank, windowSize)
    %Take average of 15*15 window and compute te energy of each pixel
   
    %Step1: Pad the image bank
    PaddedImageBank = zeros(464,614);
    for i = 1:15
       PaddedImageBank(:,:,i) = padImage(ImageBank(:,:,i), windowSize);
    end
    %Step2: Compute Energy of a 15*15 window size and replace the value
    %with center pixel
    EnergyMatrix = zeros(450, 600);
    for imgs = 1:15
        %iterate through each image
        for row = 8:464-7
            for col = 8:614-7
                  %take average of 5*5 patch
                  energy = 0;
                  for i = -7:7
                    for j = -7:7
                        energy = energy+abs(PaddedImageBank(row+i, col+j, imgs));                       
                    end                
                  end
                  EnergyMatrix(row-7, col-7, imgs) = energy/(windowSize * windowSize);                  
            end
        end
    end    
end