function dimensionReducedFeatures = PCA_seg(featureMatrix)
    data_std = zscore(featureMatrix);
    %Covariance matrix
    sigma = (1/270000)*(data_std')*(data_std);
    %apply SVD to sigma
    [U, S, V] = svd(sigma);
    Ured = U(:,1:3);
    %finding k dim subspace (k = 3)
    subspace = Ured'*data_std'; 
    x = subspace(1,:)'; %First principal component
    y = subspace(2,:)'; %Second principal component
    z = subspace(3,:)'; %third principal component
    dimensionReducedFeatures = subspace';
    scatter3(x,y,z, 'r');
    xlabel('First Principal component');
    ylabel('Second Principal component');
    zlabel('Third Principal component');
end
