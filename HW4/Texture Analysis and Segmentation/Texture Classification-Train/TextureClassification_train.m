% Name: Shashank Nelamangala Sridhara
% USC ID Number: 2082227554
% USC Email: nelamang@usc.edu
% Submission Date: 03/22/2020

function RandomForestModel = TextureClassification_train()

    filterBank = LawsFilters_train();
    %Reading all training images
    blanketTraining = zeros(128, 128);
    brickTraining = zeros(128, 128);
    grassTraining = zeros(128, 128);
    riceTraining = zeros(128, 128);
    
    %Reading training images
    for i=1:9
       blanketfileName = strcat('/home/shashankns/Desktop/Masters/2nd_sem/EE569-Image_Processing/Assignments/hw_4/Problem1/train/blanket',num2str(i),'.raw');
       brickfileName = strcat('/home/shashankns/Desktop/Masters/2nd_sem/EE569-Image_Processing/Assignments/hw_4/Problem1/train/brick',num2str(i),'.raw');
       grassfileName = strcat('/home/shashankns/Desktop/Masters/2nd_sem/EE569-Image_Processing/Assignments/hw_4/Problem1/train/grass',num2str(i),'.raw');
       ricefileName = strcat('/home/shashankns/Desktop/Masters/2nd_sem/EE569-Image_Processing/Assignments/hw_4/Problem1/train/rice',num2str(i),'.raw');
        
       blanketTraining(:,:,i) = readraw_train(blanketfileName);
       brickTraining(:,:,i) = readraw_train(brickfileName);
       grassTraining(:,:,i) =  readraw_train(grassfileName);
       riceTraining(:,:,i) = readraw_train(ricefileName);
    end
    
     labels = [0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3]';
     %Reduce illumination
     blanketTraining_illum = Reduce_Illumination_train(blanketTraining);
     brickTraining_illum = Reduce_Illumination_train(brickTraining);
     grassTraining_illum = Reduce_Illumination_train(grassTraining);
     riceTraining_illum = Reduce_Illumination_train(riceTraining);
     
     %apply law's filters to each image to obtain a feature matrix
     blanketFeatureMatrix = ApplyLawsFilters_train(filterBank,blanketTraining_illum);
     brickFeatureMatrix = ApplyLawsFilters_train(filterBank,brickTraining_illum);
     grassFeatureMatrix = ApplyLawsFilters_train(filterBank, grassTraining_illum);
     riceFeatureMatrix = ApplyLawsFilters_train(filterBank, riceTraining_illum);
     
     %concatenating matrices (36*25 dimensional matrix)
     featureMatrix = [blanketFeatureMatrix; brickFeatureMatrix; grassFeatureMatrix;riceFeatureMatrix];
     
     %Reducing features from 25 to 15 (36*15 dimensional matrix)
     reducedFeatureMatrix = reducingFeatures_train(featureMatrix);
     
     %To find descriminant power
     discriminantPower = discriminantPower_train(reducedFeatureMatrix);
     %Apply PCA to reduce the feature dimension to 3 (3*36 matrix)
     PCAReducedFeatureMatrix = PCA_train(reducedFeatureMatrix); 
     
     %SVM classifier
     %SVMModel = SupportVectorMachine_train(PCAReducedFeatureMatrix,labels);
     
     %Random Forest Classifier
     RandomForestModel = RandomForestClassifier(PCAReducedFeatureMatrix, labels);
end