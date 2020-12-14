/**
 * @file graph_utils.cpp
 * @author Ryan LaVigne
 * @brief Supporting Functions
 * @date 12-11-2020
 * @credit Lab10.2 modified to work
 */

#include <graph_utils.h>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

void printVector(std::vector <double> const &a)
{
   cout << endl;
    std::cout << "Vector: ";

    for(int i = 0; i < a.size(); i++)
        std::cout << a.at(i) << ' ';

}