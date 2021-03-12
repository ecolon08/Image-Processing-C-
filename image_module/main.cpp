#include <iostream>

#define BMP_HEADER_SIZE     54
#define BMP_COLOR_TABLE_SIZE    1024
#define CUSTOM_IMG_SIZE     1024 * 1024

using namespace std;

void imageReader(const char *imgName,
                 int *_height,
                 int *_width,
                 int *_bitDepth,
                 unsigned char *_header,
                 unsigned char *_colorTable,
                 unsigned char *_buf);

void imageWriter(const char *imgName,
                 unsigned char *header,
                 unsigned char *colorTable,
                 unsigned char *buf,
                 int bitDepth);

int main() {

    // testing the imageReader and imageWriter functions
    int imgWidth, imgHeight, imgBitDepth;
    unsigned char imgHeader[BMP_HEADER_SIZE];
    unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
    unsigned char imgBuffer[CUSTOM_IMG_SIZE];

    const char imgName[] = "images/man.bmp";
    const char newImgName[] = "images/man_copy.bmp";

    imageReader(imgName, &imgWidth, &imgHeight, &imgBitDepth, &imgHeader[0], &imgColorTable[0], &imgBuffer[0]);

    // write output image
    imageWriter(newImgName, imgHeader, imgColorTable, imgBuffer, imgBitDepth);

    // print status
    cout << "Success!" << endl;

    return 0;
}

void imageReader(const char *imgName,
                 int *_height,
                 int *_width,
                 int *_bitDepth,
                 unsigned char *_header,
                 unsigned char *_colorTable,
                 unsigned char *_buf)
{
    /*
     * Function to read in BMP image
     */

    int i;

    // create a file to read image
    FILE *streamIn;

    // read image
    streamIn = fopen(imgName, "rb");

    // check for nullptr
    if (streamIn == (FILE *)0)
        {
            cout << "Unable to open image" << endl;
        }

    // read BMP image header
    for (i = 0; i < 54; i++)
        {
            _header[i] = getc(streamIn);
        }

    // extract image height, width, and depth
    *_width = *(int *)&_header[18];
    *_height = *(int *)&_header[22];
    *_bitDepth = *(int *)&_header[28];

    // check whether color table exists, read it
    if (*_bitDepth <= 8)
        {
            fread(_colorTable, sizeof(unsigned char), 1024, streamIn);
        }

    // read pixel information into buf variable
    fread(_buf, sizeof(unsigned char), CUSTOM_IMG_SIZE, streamIn);

    // close file
    fclose(streamIn);
}


void imageWriter(const char *imgName,
                 unsigned char *header,
                 unsigned char *colorTable,
                 unsigned char *buf,
                 int bitDepth)
{
    // create a new file to write to
    FILE * fo = fopen(imgName, "wb");

    // write image header
    fwrite(header, sizeof(unsigned char), 54, fo);

    // check bitDepth to determine whether we need to write to a color table
    if (bitDepth <= 8)
        {
            fwrite(colorTable, sizeof(unsigned char), 1024, fo);
        }

    // write pixel data
    fwrite(buf, sizeof(unsigned char), CUSTOM_IMG_SIZE, fo);

    // close file
    fclose(fo);
}
