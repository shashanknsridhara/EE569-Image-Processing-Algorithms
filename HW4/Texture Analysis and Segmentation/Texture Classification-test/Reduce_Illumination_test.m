function reducedTraining = Reduce_Illumination_test(TrainingImages)
    
    %Calculate average pixel value of each image and subtract each pixel by
    %it's average
    reducedTraining = TrainingImages;
    for i = 1:12
       img = TrainingImages(:,:,i);
       pixel = 0;
       for row = 1:128
          for col = 1:128
              pixel = pixel + img(row,col);
          end
       end
       average = (pixel/(128*128));
       for row = 1:128
          for col = 1:128
              reducedTraining(row, col, i) = img(row, col)- average;
          end
       end
    end
end