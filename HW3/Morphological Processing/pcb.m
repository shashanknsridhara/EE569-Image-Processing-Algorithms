pcb_image = imread('/home/shashankns/Desktop/Masters/2nd_sem/EE569-Image_Processing/Oral Exam/HW3/Problem2/PCB.jpg');
for i = 1:239
    for j = 1:372
        if pcb_image(i,j) > 127
            pcb_image(i,j)=255;
        else
            pcb_image(i,j)=0;
        end
    end
end

shrink_pcb = bwmorph(pcb_image,'shrink');
shrink_pcb = bwmorph(shrink_pcb,'shrink');
shrink_pcb = bwmorph(shrink_pcb,'shrink');
counter = 0;
for i = 1:239
    for j = 1:372
        if shrink_pcb(i,j) == 1
             if shrink_pcb(i-1,j) == 0 && shrink_pcb(i+1,j) == 0 && shrink_pcb(i,j-1) == 0 && shrink_pcb(i,j+1) == 0 && shrink_pcb(i-1,j+1) == 0 && shrink_pcb(i+1,j+1) == 0 && shrink_pcb(i+1,j-1) == 0 && shrink_pcb(i-1,j-1) == 0
                counter=counter+1;
             end
        end
            
    end
end
disp (counter)
imshow(shrink_pcb);