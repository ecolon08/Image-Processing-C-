#include <iostream>
#include "ImageProcessing.h"

using namespace std;

int main() {

    // define variables for our class object
    int imgWidth;
    int imgHeight;
    int imgBitDepth;
    unsigned char imgHeader[BMP_HEADER_SIZE];
    unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
    unsigned char imgInBuffer[_512by512_IMG_SIZE];
    unsigned char imgOutBuffer[_512by512_IMG_SIZE];

    // define input image and output image names
    const char imgName[] = "images/girlface.bmp";
    const char newImgName[] = "images/girlface_copy.bmp";

    // create instance of our class
    ImageProcessing *myImage = new ImageProcessing(imgName,
                                                   newImgName,
                                                   &imgHeight,
                                                   &imgWidth,
                                                   &imgBitDepth,
                                                   &imgHeader[0],
                                                   &imgColorTable[0],
                                                   &imgInBuffer[0],
                                                   &imgOutBuffer[0]);

    // read image
    myImage -> readImage();

    // copy image
    myImage -> copyImageData(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE);

    // write image
    myImage -> writeImage();

    cout << "Success!" << endl;

    //std::cout << "Hello, World!" << std::endl;
    return 0;
}
