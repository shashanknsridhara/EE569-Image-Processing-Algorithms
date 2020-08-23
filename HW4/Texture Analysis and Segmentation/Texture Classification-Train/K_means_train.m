function classes = K_means_train(FeatureMatrix)
    classes = kmeans(FeatureMatrix, 4);
end