//
//  ProductODataObj.hpp
//  Optimised Approach for Product Printing.
//  In this approach, we keep the fields data stored in the given way :
//
//
//  SYM --> Field1 --> [All FieldNode having the values of Field1]
//          Field2 --> [All FieldNode having the values of Field2]
//          Field3 --> [All FieldNode having the values of Field3]
//
//
// Product :
//----------------
//      - Two Pointers are kept at the starting indexes when time >= startTime [Found using Binary Search]
//      - If the Pointers point to entries with the same uuid_, It means they correspond to the same Tick data. It is accounted into and both the pointers are incremented.
//        - Otherwise, the index of the pointer, pointing to the older index is increased.
//        - This is an optimised version, as we donot go over the rows which have none of the queried fields. So, it perform better with low occuring fields.
//        With the high occuring fields, anyhow a complete iteration is required.
//        - One Probable Optimisation with high occuring fields would be to use a Segment Tree Data Structure which can store the range queries of given 2 high queried fields.
//
//  Print :
//  --------
//  - THe printing is done by identifying the index of every field for a given symbol such that the timestamp >= startTime
//  - Fields having the same uuid_ are printed together as they belong to the same row.
//  - Their indexes are incremented and the upcoming indexes are entered into a minHeap to determine the next minimum ELement.
//
//
//
//
//

#ifndef ProductODataObj_hpp
#define ProductODataObj_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <map>
#include <ctime>
#include "IDataObj.h"
#include "PrintONode.h"
#include "FieldNode.h"


class ProductODataObj : public IDataObj{
private:
    int counter_;
    std::unordered_map<std::string, int> fieldLookUpMap;
    std::unordered_map<int, std::string> reverseFieldLookup;
    std::unordered_map<std::string, int> symbolLookUpMap;
    std::unordered_map<int, std::vector<std::pair<int, std::vector<FieldNode*>>>> symbolToFieldMap_;
    
    std::size_t searchIndex(std::vector<FieldNode*>& myVec, std::time_t startTime);
    std::size_t searchIndex(std::vector<PrintONode*>& myVec, std::time_t startTime);
    void resetData();
    std::string getSymbolName(std::string& inputString);
    
public :
    void readFile(std::string& fileName);
    void print(time_t startTime, time_t endTime, std::string& symbolString);
    void product(time_t startTime, time_t endTime, std::string& symbolString, std::string& field1, std::string& field2);
    ~ProductODataObj(){
        
    }
    
};

#endif /* ProductODataObj_hpp */
