/*
 * Filename:  CSVReader.h
 *
 * Purpose:       Definitions for the CSVReader class
 * Usage:         A class to read data from a csv file.
 ****************************************************/

#ifndef CSV_Reader_H
#define CSV_Reader_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

class CSVReader
{
        std::string fileName;
        std::string delimeter;

public:
          // Set the delimeter to a ":" charater and initialize the Class's Var's
        CSVReader(std::string filename, std::string delm = ":") :
                        fileName(filename), delimeter(delm)
        { }

        // Function to fetch data from a CSV File
        std::vector<std::vector<std::string> > readData();
};

#endif
