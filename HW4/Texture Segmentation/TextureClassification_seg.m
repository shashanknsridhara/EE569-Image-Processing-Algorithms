function PCAReducedTestFeatureMatrix = TextureSegmentation
()

    filterBank = LawsFilters_test();
    %Reading all training images
    testImages = zeros(128, 128);    
    %Reading training images
    for i=1:12
       testFileName = strcat('/home/shashankns/Desktop/Masters/2nd_sem/EE569-Image_Processing/Assignments/hw_4/Problem1/test/',num2str(i),'.raw');
       testImages(:,:,i) = readraw_test(testFileName);
    end
    
     %Reduce illumination
     testImages_illum = Reduce_Illumination_test(testImages);

     %apply law's filters to each image to obtain a feature matrix
     testFeatureMatrix = ApplyLawsFilters_test(filterBank,testImages_illum);
     
     %Reducing features from 25 to 15 (12*15 dimensional matrix)
     reducedTestFeatureMatrix = reducingFeatures_test(testFeatureMatrix);
     
     %To find descriminant power
     
     %Apply PCA to reduce the feature dimension to 3 (3*36 matrix)
     PCAReducedTestFeatureMatrix = PCA_test(reducedTestFeatureMatrix);  
end