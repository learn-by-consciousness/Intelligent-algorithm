from decodeMinist import *
from nueralnet import *

train_images = decode_idx3_ubyte(train_images_idx3_ubyte_file)
train_labels = decode_idx1_ubyte(train_labels_idx1_ubyte_file)
test_images = decode_idx3_ubyte(test_images_idx3_ubyte_file)
test_labels = decode_idx1_ubyte(test_labels_idx1_ubyte_file)
trainingimages = [(im / 255).reshape(1, 784) for im in train_images] 
traininglabels = [vectorized_result(int(i)) for i in train_labels]
testimages = [(im / 255).reshape(1, 784) for im in test_images]
testlabels = [l for l in test_labels]

net = NueraLNet([784, 30, 10])
net.train_net(trainingimages, traininglabels, 20, 3, 10, testimages, testlabels)
print("end")
