
% Name: Shashank Nelamangala Sridhara
% USC ID Number: 2082227554
% USC Email: nelamang@usc.edu
% Submission Date: 03/22/2020

function reducedFeatureMatrix = TextureSegmentation()
    filterBank = LawsFilters_seg(); 
    %Reading The Image
    testFileName = strcat('/home/shashankns/Desktop/Masters/2nd_sem/EE569-Image_Processing/Assignments/hw_4/Problem1/TextureSegmentation/comp.raw');
    SegmentationImage = readraw_seg(testFileName);
    
    %Defining the Window size
    windowSize = 15;
    paddedImage = padImage(SegmentationImage, windowSize);
    
    %Reduce illumination
    %paddedImage_illum = Reduce_Illumination_seg(paddedImage, window);

    %apply law's filters to each image to obtain a feature matrix
    ImageBank = ApplyLawsFilters_seg(filterBank,paddedImage);
    
    %Computer Energy feature of each response
    EnergyMatrix = EnergyFeature(ImageBank,windowSize);
    
    %Reduce to 14 dimenstional features using L5'L5
    NormalizedEnergyMatrix = FeatureNormalization(EnergyMatrix);
    
    %Convert this image bank to a feature matrix
    FeatureMatrix = FeatureMatrixConstruction(NormalizedEnergyMatrix);
    
    %Applying PCA
    reducedFeatureMatrix = PCA_seg(FeatureMatrix);
    
    %kmeans clustering
    classificationVector = kmeans(reducedFeatureMatrix, 6);
    
    
    %create segmentation image
    segmentationImage = CreateSegmentationImage(classificationVector);
    
    %postprocessing to improve the result
    holeFilledImage = imfill(segmentationImage);
    holeFilledImage = imfill(holeFilledImage);
    holeFilledImage = imfill(holeFilledImage);
    holeFilledImage = imfill(holeFilledImage);
  
    %Display image
    imshow(uint8(holeFilledImage), []);
end