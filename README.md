# Image-Thresholding-

Basic thresholding of an image using OpenCV library with trackbar

## What is the threshold of an image?

Image thresholding is a simple form of image segmentation. It is a way to create a binary image from grayscale or full-color image. This is typically done to separate "object" or foreground pixels from background pixels to aid in image processing.

## Basic requirements

In this project, we use the [OpenCV library](https://opencv.org/releases/), so in the first step, we have to install it completely
Then the **include_path** must be added to the our project so that the library is fully known

## Threshold Roadmap

First, we have to convert the input image to a gray channel and then scroll it pixel by pixel and compare it with the threshold number, if the number is towards 255 it will be a white pixel and if it is towards 0 it will be a pixel. Be black
Finally, we design a trackbar with a maximum value of 255 so that the user can find the variable number without re-running the program to achieve the best result.

### Threshold result :

![thresholding ](/Readme-asset/shot.png?raw=true "thresholding result image")

## What Is Convolving?

Convolution is a simple mathematical operation fundamental to many standard image processing operators. Convolution provides a way of multiplying two arrays of numbers, generally of different sizes, but of the same dimensionality, to produce a third array of numbers of the same dimensionality.

## Convolution RoadMap

For this, we need a kernel with an odd length and width that we can find its middle point and move on the image matrix to change the values of the original image matrix using the corresponding multiplication of two matrices and store it in a new matrix. With this, we can apply all kinds of image filters to our image. We have two types of convolution, one with padding and the other without padding
The use of padding is to keep the size of the final image equal to the original image, and if we remove the padding, the size of the output image will decrease compared to the original image.

### Convolution result :

![Convolution ](/Readme-asset/Convolve.jpg?raw=true "Convolving result image")

## Make and Run

You can also run the program by creating a MakeFile, but the suggested way to run the program is .

### make:

    g++ main.cpp -o main `pkg-config --cflags --libs opencv4`

### Run:

    ./main
