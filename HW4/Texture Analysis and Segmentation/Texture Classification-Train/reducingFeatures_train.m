% Name: Shashank Nelamangala Sridhara
% USC ID Number: 2082227554
% USC Email: nelamang@usc.edu
% Submission Date: 03/22/2020

function reducedFeatureMatrix = reducingFeatures_train(featureMatrix)
    reducedFeatureMatrix = zeros(36, 15);
    for i=1:36
        reducedFeatureMatrix(i,1)= featureMatrix(i,1);
        reducedFeatureMatrix(i,2)= (featureMatrix(i,2) + featureMatrix(i,6))/2;
        reducedFeatureMatrix(i,3)= (featureMatrix(i,8) + featureMatrix(i,12))/2;
        reducedFeatureMatrix(i,4)= featureMatrix(i,7);
        reducedFeatureMatrix(i,5)= (featureMatrix(i,3) + featureMatrix(i,11))/2;
        reducedFeatureMatrix(i,6)= (featureMatrix(i,9) + featureMatrix(i,17))/2;
        reducedFeatureMatrix(i,7)= featureMatrix(i,13);
        reducedFeatureMatrix(i,8)= (featureMatrix(i,4) + featureMatrix(i,16))/2;
        reducedFeatureMatrix(i,9)= (featureMatrix(i,10) + featureMatrix(i,22))/2;
        reducedFeatureMatrix(i,10)= featureMatrix(i,19);
        reducedFeatureMatrix(i,11)= (featureMatrix(i,5) + featureMatrix(i,21))/2;
        reducedFeatureMatrix(i,12)= (featureMatrix(i,14) + featureMatrix(i,18))/2;
        reducedFeatureMatrix(i,13)= featureMatrix(i,25);
        reducedFeatureMatrix(i,14)= (featureMatrix(i,20) + featureMatrix(i,24))/2;
        reducedFeatureMatrix(i,15)= (featureMatrix(i,15) + featureMatrix(i,23))/2;
    end
end