# Name: Shashank Nelamangala Sridhara
# USC ID Number: 2082227554
# USC Email: nelamang@usc.edu
# Submission Date: 04/07/2020
from __future__ import print_function
import torch
import torchvision
from torchvision import transforms, datasets
import torch.nn as nn
import torch.nn.functional as Func
import matplotlib.pyplot as plt
import torch.optim as optim


class Net(nn.Module):
    
    def __init__(self):
        super(Net, self).__init__()
        #model = EfficientNet.from_pretrained(model_name)
        #self.model = model

        #Defining 2 convolution layers
        self.convotionLayer1 = nn.Conv2d(3, 6, 5)
        self.convotionLayer2 = nn.Conv2d(6, 16, 5)
        #Defining Fully connected Layers (y = Wx + b)
        self.fullyConnected1 = nn.Linear(16 * 5 * 5, 120)
        self.fullyConnected2 = nn.Linear(120, 84)
        self.fullyConnected3 = nn.Linear(84, 10)

    def forward(self, imageFeatures):
        imageFeatures = Func.max_pool2d(Func.relu(self.convotionLayer1(imageFeatures)), (2, 2))
        # If the size is a square you can only specify a single number
        imageFeatures = Func.max_pool2d(Func.relu(self.convotionLayer2(imageFeatures)), (2,2))
        imageFeatures = imageFeatures.view(-1, 16*5*5)
        imageFeatures = Func.relu(self.fullyConnected1(imageFeatures))
        imageFeatures = Func.relu(self.fullyConnected2(imageFeatures))
        imageFeatures = self.fullyConnected3(imageFeatures)
        return imageFeatures


    def num_flat_features(self, imageFeatures):
        length = imageFeatures.size()[1:]  # all dimensions except the batch dimension
        featureDim = 1
        for k in length:
            featureDim *= k
        return featureDim

def ProcessData():
        #Load the CIFAR10 dataset.
    trainSet = datasets.CIFAR10("/home/shashankns/Desktop/Masters/2nd_sem/EE569-Image_Processing/Assignments/hw_5",
        train = True, download = True, 
        transform = transforms.Compose([transforms.ToTensor()]))
    testSet = datasets.CIFAR10("/home/shashankns/Desktop/Masters/2nd_sem/EE569-Image_Processing/Assignments/hw_5", 
        train = False, download = True, 
        transform = transforms.Compose([transforms.ToTensor()]))
    trainImages = torch.utils.data.DataLoader(trainSet, batch_size = 10, shuffle = True)
    testImages = torch.utils.data.DataLoader(testSet, batch_size = 10, shuffle = True)

    return trainImages, testImages

def evalAccuracy(trainImages, testImages):
    #Overall train and test accuracy
    correctClassification_train = 0
    totalImages_train = 0

    correctClassification_test = 0
    totalImages_test = 0

    with torch.no_grad():
        for data in trainImages:
            img, label = data
            output = cnn(img)
            for i,k in enumerate(output):
                if torch.argmax(k) == label[i]:
                    correctClassification_train +=1
                totalImages_train +=1

    with torch.no_grad():
        for data in testImages:
            img, label = data
            output = cnn(img)
            for i,k in enumerate(output):
                if torch.argmax(k) == label[i]:
                    correctClassification_test +=1
                totalImages_test +=1

    trainAccuracy = correctClassification_train/totalImages_train      
    testAccuracy = correctClassification_test/totalImages_test
    return trainAccuracy, testAccuracy


def training(trainImages, testImages, learningRate, momentum, epochs, criterion, optimizer):
    trainingAccuracyList = []
    testingAccuracyList = []

    running_loss = 0
    for epoch in range(epochs):
        for i, trainData in enumerate(trainImages, 0):
            imgs, labels = trainData

            #set the gradient to zero
            optimizer.zero_grad()
            outputs = cnn(imgs)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()
      
        print(loss)
      
    
    trainAccuracy, testAccuracy = evalAccuracy(trainImages, testImages)
    trainingAccuracyList.append(trainAccuracy)
    testingAccuracyList.append(testAccuracy)

    return trainingAccuracyList, testingAccuracyList

def plotAccuracy(trainingAccuracyList, testingAccuracyList):
    epochList = [i for i in range(1, 61)]
    plt.plot(epochList, trainingAccuracyList, label = "Train")
    plt.plot(epochList, testingAccuracyList, label = "Test")

    plt.xlabel('Number of Epochs') 
    plt.ylabel('Accuracy')  
    plt.title('Accuracy vs Epochs') 
    plt.legend()  
    plt.show() 


trainImages, testImages = ProcessData()
cnn = Net() 
#define training parameters
learningRate = 0.001
momentum = 0.9
epochs = 60
criterion = nn.CrossEntropyLoss()
optimizer = optimizer = optim.SGD(cnn.parameters(), lr=0.001, momentum=0.9)


trainingAccuracyList, testingAccuracyList = training(trainImages, testImages, learningRate, momentum, epochs, criterion, optimizer)

plotAccuracy(trainingAccuracyList, testingAccuracyList)


