
% Name: Shashank Nelamangala Sridhara
% USC ID Number: 2082227554
% USC Email: nelamang@usc.edu
% Submission Date: 03/22/2020

function FeatureMatrix = FeatureMatrixConstruction(NormalizedEnergyMatrix)        
    HEIGHT = 450;
    WIDTH = 600;
    nums = 14;
    rowSize = HEIGHT*WIDTH;
    FeatureMatrix = zeros(rowSize, nums);
    count = 1;
    for rows = 1:HEIGHT
        for cols = 1:WIDTH
            for imgs = 1:nums
                FeatureMatrix(count, imgs) = NormalizedEnergyMatrix(rows, cols, imgs); 
            end
            count = count+1;
        end
    end
end