/**
 * @file supportLib.h
 * @brief supports graph
 * @credit written by: https://github.com/InductiveComputerScience/pbPlots/tree/v0.1.8.0
 */

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

unsigned char *DoubleArrayToByteArray(vector<double> *data);
void WriteToFile(vector<double> *data, string filename);
vector<double> *ByteArrayToDoubleArray(vector<unsigned char> *data);
