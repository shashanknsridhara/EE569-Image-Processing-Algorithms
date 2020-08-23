
% Name: Shashank Nelamangala Sridhara
% USC ID Number: 2082227554
% USC Email: nelamang@usc.edu
% Submission Date: 03/22/2020

function dimensionReducedFeatures = PCA_train(featureMatrix)
    data_std = zscore(featureMatrix);
    %Covariance matrix
    sigma = (1/36)*(data_std')*(data_std);
    %apply SVD to sigma
    [U, S, V] = svd(sigma);
    Ured = U(:,1:3);
    %finding k dim subspace (k = 3)
    subspace = Ured'*data_std';
    dimensionReducedFeatures = subspace';
    x = subspace(1,:)'; %First principal component
    y = subspace(2,:)'; %Second principal component
    z = subspace(3,:)'; %third principal component 
    %Seggregating according to labels
    x1 = x(1:9,:); y1 = y(1:9,:);z1 = z(1:9,:);
    x2 = x(10:18,:);y2 = y(10:18,:); z2 = z(10:18,:);
    x3 = x(19:27,:); y3 = y(19:27,:); z3 = z(19:27,:);
    x4 = x(28:36,:);y4 = y(28:36,:); z4 = z(28:36,:);
    %Plotting
    scatter3(x1,y1,z1, 'r'); hold on;
    scatter3(x2, y2, z2, 'g');hold on;
    scatter3(x3, y3, z3, 'b'); hold on;
    scatter3(x4, y4, z4, 'c'); hold off
    xlabel('First Principal component');
    ylabel('Second Principal component');
    zlabel('Third Principal component');
    title('Train images');
end
