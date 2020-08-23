

function varianceVectors = discriminantPower_train(featureMatrix)
    varianceVectors = zeros(15, 1);
    for i = 1:15
       varianceVectors(i) = var(featureMatrix(:,i));
    end
end