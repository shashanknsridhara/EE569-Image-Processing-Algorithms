function canny_edge()
    InputImage = imread('/home/shashankns/Desktop/Masters/2nd_sem/EE569-Image_Processing/Oral Exam/HW2/Problem1/Dogs.jpg');
    threshold = [0.02, 0.6];
    Igray = rgb2gray(InputImage);
    [cannyEdge, threshOut] = edge(Igray,'canny', threshold);
    figure;
    edgeMap = imcomplement(cannyEdge);
    imshow(edgeMap);
    title('Canny Edge detector');
    disp(threshOut);
    