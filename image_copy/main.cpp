#include <iostream>
//#include <stdio.h>
//#include <cstdlib>
//#include <cstdio>

using namespace std;

int main() {

    // create a file to read image data
    FILE *streamIn = fopen("./images/cameraman.bmp","rb");

    // create a file to store the output image
    FILE *fo = fopen("./images/cameraman_copy.bmp", "wb");

    // check if file open was successful
    if(streamIn == (FILE*)0)
    {
        std::cout << "Unable to open file" << std::endl;
        //printf("Unable to open file\n");
    }

    // create variables to hold image header and color table for bmp
    // image header is 54 bytes
    // color table is 1024 bytes
    unsigned char header[54];
    unsigned char colorTable[1024];

    // extract image header using a loop
    for(int i = 0; i < 54; i++)
    {
        header[i] = getc(streamIn);
    }

    // from the image data, we can extract the image height, width, and bit depth

    // width information is at offset 18
    int width = *(int *) &header[18];
    int height = *(int *) &header[22];
    int bitDepth = *(int *) &header[28];

    // check if bit depth is less than or equal to 8, if true, need to read color table
    if (bitDepth <= 8)
    {
        fread(colorTable, sizeof(unsigned char), 1024, streamIn);
    }

    // write image header to our output file
    fwrite(header, sizeof(unsigned char), 54, fo);

    // now we need to create a buffer to store the image data/pixels
    unsigned char buf[height * width];

    // read pixel values into our buffer
    fread(buf, sizeof(unsigned char), (height * width), streamIn);

    // write color table if it exists
    if (bitDepth <= 8)
    {
        fwrite(colorTable, sizeof(unsigned char), 1024, fo);
    }

    // write pixel data into output image
    fwrite(buf, sizeof(unsigned char), (height * width), fo);

    // close files
    fclose(fo);
    fclose(streamIn);

    // report status
    cout << "Success!" << endl;

    cout << "Width : " << width << endl << "Height : " << height << endl;

    return 0;
}
