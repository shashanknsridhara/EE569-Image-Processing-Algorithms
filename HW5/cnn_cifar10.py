# Name: Shashank Nelamangala Sridhara
# USC ID Number: 2082227554
# USC Email: nelamang@usc.edu
# Submission Date: 05/03/2020


#!pip install torchvision
#!pip install efficientnet_pytorch
#from google.colab import drive
import torch
import torchvision
from torchvision import transforms, datasets
import matplotlib.pyplot as plt
import torch.nn as nn
import torch.nn.functional as Func
#drive.mount('/content/drive')

#Preprocess the data
trainSet = datasets.CIFAR10("drive/My Drive/EE569-Reports/hw_5", train = True, download = True, 
            transform = transforms.Compose([transforms.RandomHorizontalFlip(), transforms.ToTensor(), transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5)),transforms.RandomErasing()]))
testSet = datasets.CIFAR10("drive/My Drive/EE569-Reports/hw_5",  train = False, download = True, 
        transform = transforms.Compose([transforms.ToTensor(), transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))]))
trainImages = torch.utils.data.DataLoader(trainSet, batch_size = 64, shuffle = True, num_workers=2)
testImages = torch.utils.data.DataLoader(testSet, batch_size = 1000, shuffle = True,num_workers=2)

#To check whether the data is balanced
count = 0
obj_dict = {0:0, 1:0, 2:0, 3:0, 4:0, 5:0, 6:0, 7:0, 8:0, 9:0}
for imgs in trainImages:
  Images, labels = imgs
  for l in labels:
    obj_dict[int(l)] += 1
    count +=1
print (obj_dict)

#Model 7: Weight decay, Data augmentation, Data Processsing
#Build a Neural Network

class Net(nn.Module):
    
    def __init__(self):
        super(Net, self).__init__()
        #model = EfficientNet.from_pretrained(model_name)
        #self.model = model

        #Defining 2 convolution layers
        self.convotionLayer1 = nn.Conv2d(3, 32, 3)
        #self.drop1 = nn.Dropout2d(0.2)
        self.conv1_bn = nn.BatchNorm2d(32)

        self.convotionLayer2 = nn.Conv2d(32, 32, 3, padding=1)
        self.conv2_bn = nn.BatchNorm2d(32)

        self.convotionLayer3 = nn.Conv2d(32, 64, 3)
        #self.drop3 = nn.Dropout2d(0.3)
        self.conv3_bn = nn.BatchNorm2d(64)

        self.convotionLayer4 = nn.Conv2d(64, 64, 3, padding=1)
        self.conv4_bn = nn.BatchNorm2d(64)

        self.convotionLayer5 = nn.Conv2d(64, 128, 3)
        #self.drop5 = nn.Dropout2d(0.4)
        self.conv5_bn = nn.BatchNorm2d(128)

        #Defining Fully connected Layers (y = Wx + b)
        self.fullyConnected1 = nn.Linear(128*2*2, 256)
        self.fc1_bn = nn.BatchNorm1d(256)

        self.fullyConnected2 = nn.Linear(256, 64)
        self.fc2_bn = nn.BatchNorm1d(128)

        self.fullyConnected3 = nn.Linear(64, 10)

    def forward(self, imageFeatures):
        elu = nn.ELU()

        conv1 = elu(self.conv1_bn(self.convotionLayer1(imageFeatures)))
        imageFeatures = Func.max_pool2d(conv1, (2, 2))
        #print(imageFeatures.shape)
        # If the size is a square you can only specify a single number

        imageFeatures = elu(self.conv2_bn(self.convotionLayer2(imageFeatures)))
        #print(imageFeatures.shape)

        conv3 = elu(self.conv3_bn(self.convotionLayer3(imageFeatures)))
        imageFeatures = Func.max_pool2d(conv3, (2, 2))
        #print(imageFeatures.shape)

        imageFeatures = elu(self.conv4_bn(self.convotionLayer4(imageFeatures)))
        #print(imageFeatures.shape)


        conv5 = elu(self.conv5_bn(self.convotionLayer5(imageFeatures)))
        imageFeatures = Func.max_pool2d(conv5, (2, 2))

        #print(imageFeatures.shape)

        imageFeatures = imageFeatures.view(-1, 128*2*2)
        imageFeatures = elu(self.fc1_bn(self.fullyConnected1(imageFeatures)))
        imageFeatures = elu(self.fc2_bn(self.fullyConnected2(imageFeatures)))
        imageFeatures = self.fullyConnected3(imageFeatures)
        return imageFeatures

    def num_flat_features(self, imageFeatures):
      length = imageFeatures.size()[1:]  # all dimensions except the batch dimension
      featureDim = 1
      for k in length:
        featureDim *= k
      return featureDim

cnn = Net()
print(cnn)
params = list(cnn.parameters())
print(len(params))
#print(params[0].size())

input = torch.randn(3,3,32,32)
output = cnn(input)
print(output)
labels = torch.randn(10)
labels = labels.view(1, -1) 

numberOfParams= sum(p.numel() for p in cnn.parameters() if p.requires_grad)
print(numberOfParams)

import torch.optim as optim

def evalAccuracy():
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

def training(learningRate, momentum, epochs, criterion, optimizer):
  trainingAccuracyList = []
  testingAccuracyList = []

  running_loss = 0
  for epoch in range(epochs):
    print("Epochs: ",epoch)
    for i, trainData in enumerate(trainImages, 0):
      imgs, labels = trainData

      #set the gradient to zero
      optimizer.zero_grad()
      outputs = cnn(imgs)
      loss = criterion(outputs, labels)
      #loss.requires_grad = True
      loss.backward()
      optimizer.step()
      
    print(loss)

    #Saving the Model after each Epoch
    checkpoint = {'model': Net(),
          'state_dict': cnn.state_dict(),
          'optimizer' : optimizer.state_dict()}
    #torch.save(checkpoint, 'drive/My Drive/EE569-Reports/569_competition/dropout_final_aste.pth')  
    
    trainAccuracy, testAccuracy = evalAccuracy()
    trainingAccuracyList.append(trainAccuracy)
    testingAccuracyList.append(testAccuracy)

  return trainingAccuracyList, testingAccuracyList

#define training parameters
learningRate = 0.001
momentum = 0.9
epochs = 80
criterion = nn.CrossEntropyLoss()
#optimizer= optim.SGD(cnn.parameters(), lr=0.001, momentum=0.9, weight_decay=0.0001)
optimizer= optim.Adam(cnn.parameters(), lr=0.001, betas=(0.9, 0.999), eps=1e-08, weight_decay=0.0001, amsgrad=False)
#optimizer = optim.RMSprop(cnn.parameters(), lr=0.001, alpha=0.99, eps=1e-08, weight_decay=0.0001, momentum=0.9, centered=False)

#Call training function
trainingAccuracyList, testingAccuracyList = training(learningRate, momentum, epochs, criterion, optimizer)
print("Train Accuracy for Each Epoch: ",trainingAccuracyList)
print("Test Accuracy for Each Epoch: ", testingAccuracyList)

numberOfParams= sum(p.numel() for p in cnn.parameters() if p.requires_grad)
print("Total Number of Parameters",numberOfParams)

#Overall train and test accuracy
correctClassification = 0
totalImages = 0

with torch.no_grad():
  for data in testImages:
    img, label = data
    output = cnn(img)
    for i,k in enumerate(output):
      if torch.argmax(k) == label[i]:
        correctClassification +=1
      totalImages +=1

print ("Accuracy: ", correctClassification/totalImages)

epochList = [i for i in range(1, 121)]
plt.plot(epochList, trainingAccuracyList, label = "Train")
plt.plot(epochList, testingAccuracyList, label = "Test")

plt.xlabel('Number of Epochs') 
plt.ylabel('Accuracy')  
plt.title('Accuracy vs Epochs') 
plt.legend()  
plt.show()
