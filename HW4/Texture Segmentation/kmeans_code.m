% Name: Shashank Nelamangala Sridhara
% USC ID Number: 2082227554
% USC Email: nelamang@usc.edu
% Submission Date: 03/22/2020


function [labels,clusterMatrix] = kmeans_code(featureMatrix, clusters) %#ok<STOUT>
    %Randomly initialize k cluster centroids
    centroids = randn(clusters, 3);
    lables = zeros(270000, 1);
    while(cnt < 12000)
    %iterate through all the samples and assign each sample to one of the
    %clusters
    for i = 1:270000
       % find euclidean distance between
       diff = centroids(1,:)- featureMatrix(i,:);
       minimumDist = sqrt(diff*diff');
       idx = 1;
       for j = 1:clusters
           diff = centroids(j,:)- featureMatrix(i,:);
           dist = sqrt(diff*diff');
           if(dist< minimumDist)
                minimumDist = dist;
                idx = j;
           end
       end
       clusterMatrix(i,:,idx) =featureMatrix(i,:);  %#ok<AGROW>
    end    
    %Find the average all the samles in each cluseter and update centroids
    for k = 1:clusters
       centroids(k,:) = sum(clusterMatrix(:,:,k))/sum(clusterMatrix); 
    end
    end
    %Assigning labels
    
    for k = 1:270000
        % find euclidean distance between
       diff = centroids(1,:)- featureMatrix(i,:);
       minimumDist = sqrt(diff*diff');
       idx = 1;
       for j = 1:clusters
           diff = centroids(j,:)- featureMatrix(i,:);
           dist = sqrt(diff*diff');
           if(dist< minimumDist)
                minimumDist = dist;
                idx = j;
           end
       end
       lables(i) = idx;
    end 
end