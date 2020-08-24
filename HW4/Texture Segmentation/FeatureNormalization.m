
% Name: Shashank Nelamangala Sridhara
% USC ID Number: 2082227554
% USC Email: nelamang@usc.edu
% Submission Date: 03/22/2020
function NormalizedMatrix=FeatureNormalization(EnergyMatrix)
    NormalizedMatrix = zeros(450, 600);
    
    for row = 1:450
        for col = 1:600
            normalVal = EnergyMatrix(row, col, 1);
            for imgs = 2:15
               NormalizedMatrix(row, col, imgs-1)=(EnergyMatrix(row, col, imgs))/(normalVal); 
            end           
        end
    end
end