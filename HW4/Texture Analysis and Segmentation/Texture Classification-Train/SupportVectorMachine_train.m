function trainParams = SupportVectorMachine_train(featureMatrix, labels)
    %t = templateSVM('Standardize',true,'KernelFunction','gaussian');
    trainParams = fitcecoc(featureMatrix,labels,'KernelFunction','gaussian');
end