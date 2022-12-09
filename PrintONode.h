//
//  PrintONode.h
//  Description :
//  ---------------
//  1. Representation for PrintOptimised Node
//  2. Represents every row in the ticks file.
//  3. Stores all the features in a vector<pair>.Pair has key as the name of Field and value as the value of field
//  4. Other choice would be to store it as unordered_map<string, float> , However, it would have consumed more memory as compared to vector
//      and would not have provided much advantage while printing the data because we need to iterate over all the fields.
//  5. One possible optimisation would be to use a lookUp Table to save the fieldName and use Integer ID's instead. This can save more memory if strings are larger and are repeated across the input Data.
//

#ifndef PrintONode_h
#define PrintONode_h

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <map>
#include <ctime>


class PrintONode{
public:
    std::time_t timestamp;
    std::vector<std::pair<std::string, float>> featureMap_;
    
    PrintONode(std::string& inputString){
        std::stringstream ss(inputString);
        std::string tmpString;
        getline(ss, tmpString, ',');
        this->timestamp = static_cast<std::time_t>(stoi(tmpString));
        getline(ss, tmpString, ',');
        while(getline(ss, tmpString, ',')){
            std::string valString;
            getline(ss, valString, ',');
            featureMap_.push_back({tmpString, std::stof(valString)});
        }
    }
    
    friend std::ostream& operator<<(std::ostream& out, PrintONode& printONode){
        for(auto itr = printONode.featureMap_.begin() ; itr != printONode.featureMap_.end(); ++itr){
            out << itr->first << ":" << itr->second << ",";
        }
        return out;
    }
    
};

#endif /* PrintONode_h */
