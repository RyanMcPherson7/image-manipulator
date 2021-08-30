#pragma once

#include <vector>
#include <iostream>

using namespace std;

struct Header {     //contains all the components that
                    //make up a tga file's header
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

    Header(char IDL = '0', char CMT = '0', char DTC = '0', short CMO = 0, short CML = 0,
           char CMD = '0', short xO = 0, short yO = 0, short _width = 0, short _height = 0,
           char BPP = '0', char ID = '0');

    void Print();  //prints header in formatted message

    bool operator==(const Header& rhs) const;  //returns true if headers are equal
};

struct Pixel {          //contains the components that
                        //make up an individual pixel
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    Pixel(unsigned char _red = '0', unsigned char _green = '0', unsigned char _blue = '0');

    bool operator==(const Pixel& rhs) const;
};

class Image {

    Header header;
    vector<Pixel> pixels;  //we will update this when reading in pixels from file
    unsigned int numPixels;
public:
    Image(Header& _header);  //pass in an already created header object

    unsigned int GetNumPixels();
    const Header& GetHeader();
    const vector<Pixel>& GetPixels();
    void AddPixel(const Pixel& element);  //adds element to list of pixels

    bool operator==(const Image& rhs) const;
};