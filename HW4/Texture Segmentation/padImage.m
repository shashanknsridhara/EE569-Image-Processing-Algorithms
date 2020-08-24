function paddedImage = padImage(Image, window)
    HEIGHT = 450;
    WIDTH = 600;
    paddedImage= zeros(HEIGHT+window-1, WIDTH + window-1 );
    for row = 1:HEIGHT
        for col = 1:WIDTH
            paddedImage(row+7, col+7)= Image(row, col);
        end
    end
end