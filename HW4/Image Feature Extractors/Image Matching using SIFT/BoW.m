Husky1 = [108, 52, 61, 64, 71, 106, 0, 62];
Husky2 = [185, 149, 139, 141, 0, 136, 0, 134];
Husky3 = [49, 22, 57, 63, 58, 41, 35, 48];
Puppy1 = [101, 67, 85, 70, 0, 108, 65, 89];

Husky1_3= [83, 44, 23, 101, 42, 119, 85, 27];
Husky2_3 = [169, 69, 110, 94, 94, 149, 86, 113];
Husky3_3 = [49, 22, 57, 63, 58, 41, 35, 48];
Puppy1_3 = [143, 56, 78, 47, 31, 108, 69, 53];
 
bar(Puppy1_3/(sum(Puppy1_3)));
xlabel("Visual Words (Husky 3)");
ylabel("Histogram of Feature Descriptors in Puppy 1 Image");
title("Histogram of Puppy 1 with Husky 3 centroids (Visual words)");

