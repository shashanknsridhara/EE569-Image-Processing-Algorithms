function reducedTraining = Reduce_Illumination_seg(Image, window)
    
    %Calculate average pixel value of each image and subtract each pixel by
    %it's average
    reducedTraining = Image;
    for i = 1:12
       img = Image(:,:,i);
       pixel = 0;
       for row = 1:128
          for col = 1:128
              pixel = pixel + img(row,col);
          end
       end
       average = (pixel/(128*128));
       for row = 1:128
          for col = 1:128
              Image(row, col, i) = img(row, col)- average;
          end
       end
    end
end