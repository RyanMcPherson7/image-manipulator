#pragma once

#include <fstream>
#include <string>
#include "Image.h"

//contains the reading function and different blending mode functions

void ReadTGA(vector<Image>& list, const string& fileName); //read a given file and store in given vector

void CopyTGA(vector<Image>& list, const string& fileName, Image& original); //copy an image out to a given file and store in vector

void WriteHeaderData(ofstream& stream, Image& original); //writes out original's header data to file using given stream

void Multiply(vector<Image>& list, Image& top, Image& bottom, const string& fileName); //part 1 - multiplies top and bottom channels and stores it in given vector

void Subtract(vector<Image>& list, Image& top, Image& bottom, const string& fileName); //part 2 - subtracts top from bottom channels and stores it in given vector

void Screen(vector<Image>& list, Image& top, Image& bottom, const string& fileName); //part 3 - screen blends top with bottom image and stores it in given vector

void Overlay(vector<Image>& list, Image& top, Image& bottom, const string& fileName); //part 5 - overlay blends top with bottom image and stores it in given vector

void AddGreen(vector<Image>& list, Image& original, unsigned int amount, const string& fileName); //part 6 - adds given amount to green channel to new image and stores it in given vector

void ScaleRedAndBlue(vector<Image>& list, Image& original, unsigned int redScale, //part 7 - scales (multiplies) the red and the blue channels ans stores it in given vector
                     unsigned int blueScale, const string& fileName);

void Separate(vector<Image>& list, Image& original, const string& key, const string& fileName); //part 8 - separates file into respected color channels based on given key and stores it in given vector

void Combine(vector<Image>& list, Image& red, Image& green, Image& blue, const string& fileName); //part 9 - combines the RGB components of the respected files into one and stores it in given vector

void Flip180(vector<Image>& list, Image& original, const string& fileName); //part 10 - flips the given file 180 degrees and stores it in given vector

void Quad(vector<Image>& list, Image& topL, Image& topR, Image& botL, Image& botR, const string& fileName); //extra credit - makes new image with given images placed in respected quadrants and stores in given vector