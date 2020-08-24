function featureMatrix = ApplyLawsFilters_test(filterBank, TrainingImages)
    
    featureMatrix = zeros(9,25);
    for imgs = 1:12
       Image = TrainingImages(:,:,imgs);
       for f = 1:25
           filter = filterBank(:,:,f);
           averageEnergy = convolution_test(filter, Image);
           featureMatrix(imgs, f) = averageEnergy;
       end
    end
end
