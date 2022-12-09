//
//  PrintODataObj.hpp
//  This approach is to optimise the printing Operation.
//  myMap_ : Stores the Data in unordered_map. The Key is the SymbolName. The value is the vector of PrintONode[timestamp_ and features].
//           -  While reading files, we know that the rows will always be in increasing order of timestamp. Thus, the retrieved data from a given row can be appended to the end of the vector. This will ensure that this Vector will always be sorted in non-decreasing order of time.
//
//  Optimised Approach : For Print Optimisation, we need to print all the data for a particular symbol lying within the timeframe
//     1. Locate the index in the vector with timestamp >= startTime using Binary search
//     2. Keep on iterating and printing the features until we reach the index == vector.size() or timestamp of vector[index] > endIndex
//     3. The sum of Product is found by iterating over all the indexes that lie between startTime and endTime.
//

#ifndef PrintODataObj_hpp
#define PrintODataObj_hpp

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <map>
#include <ctime>
#include "PrintONode.h"
#include "IDataObj.h"

class PrintODataObj : public IDataObj{
private:
    std::unordered_map<std::string, std::vector<PrintONode*>> myMap_;
    std::size_t searchIndex(std::vector<PrintONode*>& myVec, std::time_t startTime);
    std::string getSymbolName(std::string& inputString);
    void resetFile();
public:
    void readFile(std::string& fileName);
    void print(time_t startTime, time_t endTime, std::string& symbolString);
    void product(time_t startTime, time_t endTime, std::string& symbolString, std::string& field1, std::string& field2);
};




#endif /* PrintODataObj_hpp */
