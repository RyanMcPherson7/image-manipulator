#include "Functionality.h"

void ReadTGA(vector<Image>& list, const string& fileName) {

    ifstream inFile (fileName, ios_base::binary);  //open file in binary

    if (!(inFile.is_open()))  //if the file is not open...
        throw runtime_error("File cannot be opened");


    //Building header

    //temporarily store bytes to be put into header object
    char idLength, colorMapType, dataTypeCode, bitsPerPixel, imageDescriptor, colorMapDepth;
    short colorMapOrigin, colorMapLength, xOrigin, yOrigin, width, height;

    //reading header data
    inFile.read((char*)&idLength, 1);
    inFile.read((char*)&colorMapType, 1);
    inFile.read((char*)&dataTypeCode, 1);
    inFile.read((char*)&colorMapOrigin, 2);
    inFile.read((char*)&colorMapLength, 2);
    inFile.read((char*)&colorMapDepth, 1);
    inFile.read((char*)&xOrigin, 2);
    inFile.read((char*)&yOrigin, 2);
    inFile.read((char*)&width, 2);
    inFile.read((char*)&height, 2);
    inFile.read((char*)&bitsPerPixel, 1);
    inFile.read((char*)&imageDescriptor, 1);

    //creating image header
    Header newHeader(idLength, colorMapType, dataTypeCode, colorMapOrigin, colorMapLength,
                     colorMapDepth, xOrigin, yOrigin, width, height, bitsPerPixel, imageDescriptor);

    //creating image with header
    Image newImage(newHeader);

    //temporarily store bytes to put into pixel object
    unsigned char red, green, blue;

    //adding pixels to image's vector of pixels
    for (unsigned int i = 0; i < newImage.GetNumPixels(); i++) {

        //reading and creating each pixel
        inFile.read((char*)&blue, 1);
        inFile.read((char*)&green, 1);
        inFile.read((char*)&red, 1);

        //creates new pixel
        Pixel newPixel(red, green, blue);

        //adds created pixel to created image's vector
        newImage.AddPixel(newPixel);
    }

    //image fully loaded, add to end of image list
    list.push_back(newImage);

    //close file
    inFile.close();
}


void CopyTGA(vector<Image>& list, const string& fileName, Image& original) {

    ofstream outFile (fileName, ios_base::binary);  //open file in binary

    if (!(outFile.is_open()))  //if the file is not open...
        throw runtime_error("File cannot be opened");


    //write out header data
    WriteHeaderData(outFile, original);

    //write out the pixel data
    for (unsigned int i = 0; i < original.GetNumPixels(); i++) {

        outFile.write((char*)&original.GetPixels().at(i).blue, 1);
        outFile.write((char*)&original.GetPixels().at(i).green, 1);
        outFile.write((char*)&original.GetPixels().at(i).red, 1);
    }

    //close file
    outFile.close();

    //Read the newly created file and store it in given vector
    ReadTGA(list, fileName);
}


void WriteHeaderData(ofstream& stream, Image& original) {

    stream.write(&original.GetHeader().idLength, 1);
    stream.write(&original.GetHeader().colorMapType, 1);
    stream.write(&original.GetHeader().dataTypeCode, 1);
    stream.write((char*)&original.GetHeader().colorMapOrigin, 2);
    stream.write((char*)&original.GetHeader().colorMapLength, 2);
    stream.write(&original.GetHeader().colorMapDepth, 1);
    stream.write((char*)&original.GetHeader().xOrigin, 2);
    stream.write((char*)&original.GetHeader().yOrigin, 2);
    stream.write((char*)&original.GetHeader().width, 2);
    stream.write((char*)&original.GetHeader().height, 2);
    stream.write(&original.GetHeader().bitsPerPixel, 1);
    stream.write(&original.GetHeader().imageDescriptor, 1);
}



void Multiply(vector<Image>& list, Image& top, Image& bottom, const string& fileName) {  //PART 1

    ofstream outFile(fileName, ios_base::binary);  //open file in binary

    if (!(outFile.is_open()))  //if the file is not open...
        throw runtime_error("File cannot be opened");

    //write out header data
    WriteHeaderData(outFile, top);

    //write out the pixel data
    for (unsigned int i = 0; i < top.GetNumPixels(); i++) {

        //multiplies the individual color channels
        float blueTemp = (float)top.GetPixels().at(i).blue * (float)bottom.GetPixels().at(i).blue / 255.0f + 0.5f;
        float greenTemp = (float)top.GetPixels().at(i).green * (float)bottom.GetPixels().at(i).green / 255.0f + 0.5f;
        float redTemp = (float)top.GetPixels().at(i).red * (float)bottom.GetPixels().at(i).red / 255.0f + 0.5f;

        //coverts them back into chars
        unsigned char blue = (char)blueTemp;
        unsigned char green = (char)greenTemp;
        unsigned char red = (char)redTemp;

        //writes out new color channels
        outFile.write((char*)&blue, 1);
        outFile.write((char*)&green, 1);
        outFile.write((char*)&red, 1);
    }

    //close file
    outFile.close();

    //Read the newly created file and store it in given vector
    ReadTGA(list, fileName);
}


void Subtract(vector<Image>& list, Image& top, Image& bottom, const string& fileName) {

    ofstream outFile(fileName, ios_base::binary);  //open file in binary

    if (!(outFile.is_open()))  //if the file is not open...
        throw runtime_error("File cannot be opened");

    //write out header data
    WriteHeaderData(outFile, top);

    //write out the pixel data
    for (unsigned int i = 0; i < top.GetNumPixels(); i++) {

        //stores bottom - top channels temporarily
        int blueTemp = bottom.GetPixels().at(i).blue - top.GetPixels().at(i).blue;
        int greenTemp = bottom.GetPixels().at(i).green - top.GetPixels().at(i).green;
        int redTemp = bottom.GetPixels().at(i).red - top.GetPixels().at(i).red;

        unsigned char blue, green, red;

        if (blueTemp < 0)  //clamp value to zero if negative
            blue = 0;
        else
            blue = blueTemp;

        if (greenTemp < 0)
            green = 0;
        else
            green = greenTemp;

        if (redTemp < 0)
            red = 0;
        else
            red = redTemp;

        //writes out new color channels
        outFile.write((char*)&blue, 1);
        outFile.write((char*)&green, 1);
        outFile.write((char*)&red, 1);
    }

    //close file
    outFile.close();

    //Read the newly created file and store it in given vector
    ReadTGA(list, fileName);
}


void Screen(vector<Image>& list, Image& top, Image& bottom, const string& fileName) {

    ofstream outFile(fileName, ios_base::binary);  //open file in binary

    if (!(outFile.is_open()))  //if the file is not open...
        throw runtime_error("File cannot be opened");

    //write out header data
    WriteHeaderData(outFile, top);

    //write out the pixel data
    for (unsigned int i = 0; i < top.GetNumPixels(); i++) {

        //stores (1 - (1 - top/255) * (1 - bottom/255)) * 255 temporarily
        float blueTemp = (1 - (1 - (float)top.GetPixels().at(i).blue / 255.0f) * (1.0f - (float)bottom.GetPixels().at(i).blue / 255.0f)) * 255.0f + 0.5f;
        float greenTemp = (1 - (1 - (float)top.GetPixels().at(i).green / 255.0f) * (1.0f - (float)bottom.GetPixels().at(i).green / 255.0f)) * 255.0f + 0.5f;
        float redTemp = (1 - (1 - (float)top.GetPixels().at(i).red / 255.0f) * (1.0f - (float)bottom.GetPixels().at(i).red / 255.0f)) * 255.0f + 0.5f;

        unsigned char blue = (char)blueTemp;
        unsigned char green = (char)greenTemp;
        unsigned char red = (char)redTemp;

        //writes out new color channels
        outFile.write((char*)&blue, 1);
        outFile.write((char*)&green, 1);
        outFile.write((char*)&red, 1);
    }

    //close file
    outFile.close();

    //Read the newly created file and store it in given vector
    ReadTGA(list, fileName);
}


void Overlay(vector<Image>& list, Image& top, Image& bottom, const string& fileName) {

    ofstream outFile(fileName, ios_base::binary);  //open file in binary

    if (!(outFile.is_open()))  //if the file is not open...
        throw runtime_error("File cannot be opened");

    //write out header data
    WriteHeaderData(outFile, top);

    //write out the pixel data
    for (unsigned int i = 0; i < top.GetNumPixels(); i++) {

        //stores result of overlay algorithm temporarily
        // IF bottom / 255 < 0.5, then (2 * (top / 255) * (bottom / 255)) * 255 + 0.5
        // ELSE, then (1 - 2 * (top / 255) * (bottom / 255)) * 255 + 0.5

        float blueTemp;
        float greenTemp;
        float redTemp;

        if ((float)bottom .GetPixels().at(i).blue / 255.0f < 0.5f)
            blueTemp = (2 * (((float)top.GetPixels().at(i).blue / 255.0f) * ((float)bottom.GetPixels().at(i).blue / 255.0f))) * 255.0f + 0.5f;
        else
            blueTemp = (1 - 2 * (1 - (float)top.GetPixels().at(i).blue / 255.0f) * (1 - (float)bottom.GetPixels().at(i).blue / 255.0f)) * 255.0f + 0.5f;

        if ((float)bottom.GetPixels().at(i).green / 255.0f < 0.5f)
            greenTemp = (2 * (((float)top.GetPixels().at(i).green / 255.0f) * ((float)bottom.GetPixels().at(i).green / 255.0f))) * 255.0f + 0.5f;
        else
            greenTemp = (1 - 2 * (1 - (float)top.GetPixels().at(i).green / 255.0f) * (1 - (float)bottom.GetPixels().at(i).green / 255.0f)) * 255.0f + 0.5f;

        if ((float)bottom.GetPixels().at(i).red / 255.0f < 0.5f)
            redTemp = (2 * (((float)top.GetPixels().at(i).red / 255.0f) * ((float)bottom.GetPixels().at(i).red / 255.0f))) * 255.0f + 0.5f;
        else
            redTemp = (1 - 2 * (1 - (float)top.GetPixels().at(i).red / 255.0f) * (1 - (float)bottom.GetPixels().at(i).red / 255.0f)) * 255.0f + 0.5f;

        unsigned char blue = (char)blueTemp;
        unsigned char green = (char)greenTemp;
        unsigned char red = (char)redTemp;

        //writes out new color channels
        outFile.write((char*)&blue, 1);
        outFile.write((char*)&green, 1);
        outFile.write((char*)&red, 1);
    }

    //close file
    outFile.close();

    //Read the newly created file and store it in given vector
    ReadTGA(list, fileName);
}


void AddGreen(vector<Image>& list, Image& original, unsigned int amount, const string& fileName) {

    ofstream outFile(fileName, ios_base::binary);  //open file in binary

    if (!(outFile.is_open()))  //if the file is not open...
        throw runtime_error("File cannot be opened");

    //write out header data
    WriteHeaderData(outFile, original);

    //write out the pixel data
    for (unsigned int i = 0; i < original.GetNumPixels(); i++) {

        unsigned int greenTemp = original.GetPixels().at(i).green + amount;

        unsigned char green;

        if (greenTemp > 255)  //clamp green channel to 255 max
            green = 255;
        else
            green = greenTemp;

        //writes out new color channels (red and blue remain unchanged)
        outFile.write((char*)&original.GetPixels().at(i).blue, 1);
        outFile.write((char*)&green, 1);
        outFile.write((char*)&original.GetPixels().at(i).red, 1);
    }

    //close file
    outFile.close();

    //Read the newly created file and store it in given vector
    ReadTGA(list, fileName);
}


void ScaleRedAndBlue(vector<Image>& list, Image& original, unsigned int redScale, unsigned int blueScale, const string& fileName) {

    ofstream outFile(fileName, ios_base::binary);  //open file in binary

    if (!(outFile.is_open()))  //if the file is not open...
        throw runtime_error("File cannot be opened");

    //write out header data
    WriteHeaderData(outFile, original);

    //write out the pixel data
    for (unsigned int i = 0; i < original.GetNumPixels(); i++) {

        //adjusts red and blue channels and store value temporarily
        unsigned int blueTemp = original.GetPixels().at(i).blue * blueScale;
        unsigned int redTemp = original.GetPixels().at(i).red * redScale;

        unsigned char blue, red;

        if (blueTemp > 255)  //clamps channel values to 255 max
            blue = 255;
        else
            blue = blueTemp;

        if (redTemp > 255)
            red = 255;
        else
            red = redTemp;

        //writes out new color channels (green remains unchanged)
        outFile.write((char*)&blue, 1);
        outFile.write((char*)&original.GetPixels().at(i).green, 1);
        outFile.write((char*)&red, 1);
    }

    //close file
    outFile.close();

    //Read the newly created file and store it in given vector
    ReadTGA(list, fileName);
}


void Separate(vector<Image>& list, Image& original, const string& key, const string& fileName) {

    if (key != "red" &&  key != "green" && key != "blue")  //if an invalid key is entered...
        throw runtime_error("Invalid key");

    ofstream outFile(fileName, ios_base::binary);  //open file in binary

    if (!(outFile.is_open()))  //if the file is not open...
        throw runtime_error("File cannot be opened");

    //write out header data
    WriteHeaderData(outFile, original);

    //write out the pixel data
    if (key == "red") {  //write only red

        for (unsigned int i = 0; i < original.GetNumPixels(); i++) {

            outFile.write((char*)&original.GetPixels().at(i).red, 1);
            outFile.write((char*)&original.GetPixels().at(i).red, 1);
            outFile.write((char*)&original.GetPixels().at(i).red, 1);
        }
    }
    else if (key == "green") {  //write only green

        for (unsigned int i = 0; i < original.GetNumPixels(); i++) {

            outFile.write((char*)&original.GetPixels().at(i).green, 1);
            outFile.write((char*)&original.GetPixels().at(i).green, 1);
            outFile.write((char*)&original.GetPixels().at(i).green, 1);
        }
    }
    else {  //write only blue

        for (unsigned int i = 0; i < original.GetNumPixels(); i++) {

            outFile.write((char*)&original.GetPixels().at(i).blue, 1);
            outFile.write((char*)&original.GetPixels().at(i).blue, 1);
            outFile.write((char*)&original.GetPixels().at(i).blue, 1);
        }
    }

    //close file
    outFile.close();

    //Read the newly created file and store it in given vector
    ReadTGA(list, fileName);
}


void Combine(vector<Image>& list, Image& red, Image& green, Image& blue, const string& fileName) {

    ofstream outFile(fileName, ios_base::binary);  //open file in binary

    if (!(outFile.is_open()))  //if the file is not open...
        throw runtime_error("File cannot be opened");

    //write out header data
    WriteHeaderData(outFile, red);

    //write out the pixel data
    for (unsigned int i = 0; i < red.GetNumPixels(); i++) {

        outFile.write((char*)&blue.GetPixels().at(i).blue, 1);
        outFile.write((char*)&green.GetPixels().at(i).green, 1);
        outFile.write((char*)&red.GetPixels().at(i).red, 1);
    }

    //close file
    outFile.close();

    //Read the newly created file and store it in given vector
    ReadTGA(list, fileName);
}


void Flip180(vector<Image>& list, Image& original, const string& fileName) {

    ofstream outFile (fileName, ios_base::binary);  //open file in binary

    if (!(outFile.is_open()))  //if the file is not open...
        throw runtime_error("File cannot be opened");


    //write out header data
    WriteHeaderData(outFile, original);

    //write out the pixel data
    for (int i = (signed)original.GetNumPixels() - 1; i >= 0; i--) {  //write out the pixels in reverse

        outFile.write((char*)&original.GetPixels().at(i).blue, 1);
        outFile.write((char*)&original.GetPixels().at(i).green, 1);
        outFile.write((char*)&original.GetPixels().at(i).red, 1);
    }

    //close file
    outFile.close();

    //Read the newly created file and store it in given vector
    ReadTGA(list, fileName);
}


void Quad(vector<Image>& list, Image& topL, Image& topR, Image& botL, Image& botR, const string& fileName) {

    ofstream outFile(fileName, ios_base::binary);  //open file in binary

    if (!(outFile.is_open()))  //if the file is not open...
        throw runtime_error("File cannot be opened");


    //writing out header data
    outFile.write(&topL.GetHeader().idLength, 1);
    outFile.write(&topL.GetHeader().colorMapType, 1);
    outFile.write(&topL.GetHeader().dataTypeCode, 1);
    outFile.write((char*)&topL.GetHeader().colorMapOrigin, 2);
    outFile.write((char*)&topL.GetHeader().colorMapLength, 2);
    outFile.write(&topL.GetHeader().colorMapDepth, 1);
    outFile.write((char*)&topL.GetHeader().xOrigin, 2);
    outFile.write((char*)&topL.GetHeader().yOrigin, 2);

    //adjust height and width
    unsigned int newWidth = topL.GetHeader().width + topR.GetHeader().width;
    unsigned int newHeight = topL.GetHeader().height + botL.GetHeader().height;

    outFile.write((char*)&newWidth, 2);
    outFile.write((char*)&newHeight, 2);

    outFile.write(&topL.GetHeader().bitsPerPixel, 1);
    outFile.write(&topL.GetHeader().imageDescriptor, 1);

    //writing out pixel data

    //writing bottom 2 images
    for (unsigned int i = 0; i < newHeight / 2; i++) {

        //print left image's line
        for (unsigned int j = 0; j < newWidth / 2; j++) {

            unsigned int index = j + i * (newWidth / 2);

            outFile.write((char*)&botL.GetPixels().at(index).blue, 1);
            outFile.write((char*)&botL.GetPixels().at(index).green, 1);
            outFile.write((char*)&botL.GetPixels().at(index).red, 1);
        }

        //print right image's line
        for (unsigned int j = 0; j < newWidth / 2; j++) {

            unsigned int index = j + i * (newWidth / 2);

            outFile.write((char*)&botR.GetPixels().at(index).blue, 1);
            outFile.write((char*)&botR.GetPixels().at(index).green, 1);
            outFile.write((char*)&botR.GetPixels().at(index).red, 1);
        }
    }

    //writing top 2 images
    for (unsigned int i = 0; i < newHeight / 2; i++) {

        //print left image's line
        for (unsigned int j = 0; j < newWidth / 2; j++) {

            unsigned int index = j + i * (newWidth / 2);

            outFile.write((char*)&topL.GetPixels().at(index).blue, 1);
            outFile.write((char*)&topL.GetPixels().at(index).green, 1);
            outFile.write((char*)&topL.GetPixels().at(index).red, 1);
        }

        //print right image's line
        for (unsigned int j = 0; j < newWidth / 2; j++) {

            unsigned int index = j + i * (newWidth / 2);

            outFile.write((char*)&topR.GetPixels().at(index).blue, 1);
            outFile.write((char*)&topR.GetPixels().at(index).green, 1);
            outFile.write((char*)&topR.GetPixels().at(index).red, 1);
        }
    }

    //close file
    outFile.close();

    //Read the newly created file and store it in given vector
    ReadTGA(list, fileName);
}