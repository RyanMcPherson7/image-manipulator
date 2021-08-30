#include "Image.h"

//=================Header Functions==================

Header::Header(char IDL, char CMT, char DTC, short CMO, short CML, char CMD, short xO, short yO, short _width,
               short _height, char BPP, char ID) {

    idLength = IDL;
    colorMapType = CMT;
    dataTypeCode = DTC;
    colorMapOrigin = CMO;
    colorMapLength = CML;
    colorMapDepth = CMD;
    xOrigin = xO;
    yOrigin = yO;
    width = _width;
    height = _height;
    bitsPerPixel = BPP;
    imageDescriptor = ID;
}

void Header::Print() {

    cout << "ID Length: " << idLength << endl;
    cout << "Color Map Type: " << colorMapType << endl;
    cout << "Data type code: " << dataTypeCode << endl;
    cout << "Color Map Origin: " << colorMapOrigin << endl;
    cout << "Color Map Length: " << colorMapLength << endl;
    cout << "Color Map Depth: " << colorMapDepth << endl;
    cout << "X Origin: " << xOrigin << endl;
    cout << "Y Origin: " << yOrigin << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << "Bits per pixel: " << bitsPerPixel << endl;
    cout << "Image Descriptor: " << imageDescriptor << endl;
}

bool Header::operator==(const Header& rhs) const {

    return idLength == rhs.idLength && colorMapType == rhs.colorMapType && dataTypeCode == rhs.dataTypeCode
           && colorMapOrigin == rhs.colorMapOrigin && colorMapLength == rhs.colorMapLength
           && colorMapDepth == rhs.colorMapDepth && xOrigin == rhs.xOrigin && yOrigin == rhs.yOrigin
           && width == rhs.width && height == rhs.height && bitsPerPixel == rhs.bitsPerPixel
           && imageDescriptor == rhs.imageDescriptor;
}


//======================Pixel Functions===================

Pixel::Pixel(unsigned char _red, unsigned char _green, unsigned char _blue) {

    red = _red;
    green = _green;
    blue = _blue;
}

bool Pixel::operator==(const Pixel &rhs) const {

    return red == rhs.red && green == rhs.green && blue == rhs.blue;
}


//====================Image Functions=====================

Image::Image(Header& _header) {

    header = _header;  //calls implicitly created assignment operator, fine in this case
    numPixels = header.width * header.height;
}

const vector<Pixel>& Image::GetPixels() { return pixels; }

const Header& Image::GetHeader() { return header; }

unsigned int Image::GetNumPixels() { return numPixels; }

void Image::AddPixel(const Pixel &element) { pixels.push_back(element); }

bool Image::operator==(const Image &rhs) const {

    if (!(header == rhs.header))  //if the headers are not equal,
        return false;             //then the images are not equal

    for (unsigned int i = 0; i < numPixels; i++)
        if (!(pixels.at(i) == rhs.pixels.at(i)))  //if a single pixel is not equal,
            return false;                         //then images not equal

    return true;  //if the header and the pixels are the same,
                  //the images are equal
}