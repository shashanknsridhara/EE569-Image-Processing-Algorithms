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
