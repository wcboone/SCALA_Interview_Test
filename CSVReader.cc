/*
 *  File: CSVReader.cpp
 *
 *  Purpose:       Implementation for the CSVReader class
*   Usage:         Parses through a csv file line by line and returns the data
*                  in a Vector of Vector of strings.
****************************************************************/
#include <CSVReader.h>


std::vector<std::vector<std::string> > CSVReader::readData()
{
        std::ifstream file(fileName);

        std::vector<std::vector<std::string> > dataList;

        std::string line = "";
        // Iterate through each "line" of the input file and split the content using delimeter
        while (getline(file, line))
        {
                std::vector<std::string> vec;
                  // get each record( line) of the input file and split each item into
                  // the "vec" vector by each delimeter
                boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
                dataList.push_back(vec);       // Assign each vec item to the DataList vector
        }
        // Close the File
        file.close();

        return dataList;
}

