
% Name: Shashank Nelamangala Sridhara
% USC ID Number: 2082227554
% USC Email: nelamang@usc.edu
% Submission Date: 03/22/2020

function ImageBank = ApplyLawsFilters_seg(filterBank, paddedImage)
    
    ImageBank = zeros(450,600);
    imgs = 1;
    for f = 1:15
        filter = filterBank(:,:,f);
        convolvedImage = convolution_seg(filter, paddedImage);
        ImageBank(:,:,imgs) = convolvedImage;
        imgs=imgs+1;
    end
end
