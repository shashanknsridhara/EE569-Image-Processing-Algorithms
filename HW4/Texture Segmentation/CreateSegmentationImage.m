
% Name: Shashank Nelamangala Sridhara
% USC ID Number: 2082227554
% USC Email: nelamang@usc.edu
% Submission Date: 03/22/2020


function segmentationImage = CreateSegmentationImage(classificationVector)
    segmentationImage = zeros(450, 600);
    count = 1;
    for rows = 1:450
        for cols = 1:600
            class = classificationVector(count);
            if(class == 1)
                segmentationImage(rows, cols) = 0;        
            elseif(class == 2)
                segmentationImage(rows, cols) = 51;
            elseif(class == 3)
                segmentationImage(rows, cols) = 102;
            elseif(class == 4)
                segmentationImage(rows, cols) = 153;
            elseif(class == 5)
                segmentationImage(rows, cols) = 201;
            else
                segmentationImage(rows, cols) = 255;
            end
            count = count+1;
        end
    end
end