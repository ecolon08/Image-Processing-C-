//
// Created by ernesto on 3/12/21.
//

#include "ImageProcessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

ImageProcessing::ImageProcessing(const char * _inImgName,
                                 const char * _outImgName,
                                 int * _height,
                                 int * _width,
                                 int * _bitDepth,
                                 unsigned char * _header,
                                 unsigned char * _colorTable,
                                 unsigned char * _inBuf,
                                 unsigned char * _outBuf) {
    // constructor
     inImgName = _inImgName;
     outImgName = _outImgName;
     height = _height;
     width = _width;
     bitDepth = _bitDepth;
     header = _header;
     colorTable = _colorTable;
     inBuf = _inBuf;
     outBuf = _outBuf;

}

void ImageProcessing::readImage() {
    int i;
    FILE *streamIn;

    // open image file
    streamIn = fopen(inImgName, "rb");

    if (streamIn == (FILE *)0) {
        cout << "Unable to open image file" << endl;
        exit(0);
    }

    // extract file header
    for (i = 0; i < BMP_HEADER_SIZE; i++) {
        header[i] = getc(streamIn);
    }

    // extract height, width, and bit depth
    *width = *(int *)&header[18];
    *height = *(int *)&header[22];
    *bitDepth = *(int *)&header[28];

    // check if bit depth is <= 8 (i.e., does a color table exist?)
    if (*bitDepth <= 8) {
        fread(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, streamIn);
    }

    // read image pixel information
    fread(inBuf, sizeof(unsigned char), _512by512_IMG_SIZE, streamIn);

    // close the file
    fclose(streamIn);
}

void ImageProcessing::writeImage() {
    // open a file for writing
    FILE * fo = fopen(outImgName, "wb");

    // write the header information
    fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, fo);

    // check if color table is required
    if (*bitDepth <= 8) {
        fwrite(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, fo);
    }

    fwrite(outBuf, sizeof(unsigned char), _512by512_IMG_SIZE, fo);

    // close the file
    fclose(fo);
}

void ImageProcessing::copyImageData(unsigned char *_srcBuf, unsigned char *_destBuf, int bufSize) {
    for (int i = 0; i < bufSize; i++) {
        _destBuf[i] = _srcBuf[i];
    }

}

ImageProcessing::~ImageProcessing() {

}