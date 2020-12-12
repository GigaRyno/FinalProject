/**
 * @file graph_utils.h
 * @author Ryan LaVigne
 * @brief Final Project
 * @date 12-11-2020
 * @credit Lab10.2 modified to work
 */
#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include <string>
#include <fstream>

/**
 * @brief process data from a datalog from a CSV file
 * @param inFile ifstream to an opened and validated csv file
 * @param FileName the name of the file that you want to produce
 * @return int returns the number of records processed
 */
int processCSV(std::ifstream &inFile, std::string FileName, std::string Opt);

#endif