import numpy as np
import struct
from PIL import Image

train_images_idx3_ubyte_file = './data/train-images-idx3-ubyte/train-images.idx3-ubyte'
train_labels_idx1_ubyte_file = './data/train-labels-idx1-ubyte/train-labels.idx1-ubyte'
test_images_idx3_ubyte_file = './data/t10k-images-idx3-ubyte/t10k-images.idx3-ubyte'
test_labels_idx1_ubyte_file = './data/t10k-labels-idx1-ubyte/t10k-labels.idx1-ubyte'

def decode_idx3_ubyte(idx3_ubyte_file):
    bin_data = open(idx3_ubyte_file, 'rb').read()

    offset = 0
    fmt_header = '>iiii'
    magic_number, num_images, num_rows, num_cols = struct.unpack_from(fmt_header, bin_data, offset)

    image_size = num_rows * num_cols
    offset += struct.calcsize(fmt_header)
    fmt_image = '>' + str(image_size) + 'B'
    images = np.empty((num_images, image_size))
    for i in range(num_images):
        images[i] = np.array(struct.unpack_from(fmt_image, bin_data, offset))
        offset += struct.calcsize(fmt_image)
    return images

def decode_idx1_ubyte(idx1_ubyte_file):
    bin_data = open(idx1_ubyte_file, 'rb').read()

    offset = 0
    fmt_header = '>ii'
    magic_number, num_images = struct.unpack_from(fmt_header, bin_data, offset)

    offset += struct.calcsize(fmt_header)
    fmt_image = '>B'
    labels = np.empty(num_images)
    for i in range(num_images):
        labels[i] = struct.unpack_from(fmt_image, bin_data, offset)[0]
        offset += struct.calcsize(fmt_image)
    return labels

def vectorized_result(j):
    e = np.zeros((1, 10))
    e[0][j] = 1.0
    return e
