//
//  FieldNode.h
//  Class to hold uniqueID, timestamp and fieldValue of a paricular field and belonging to a particular row in the ticks table
//  This is used in Product Optimised Approach.
//

#ifndef FieldNode_h
#define FieldNode_h

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <map>
#include <ctime>

class FieldNode{
public:
    int uuid_;
    std::time_t timestamp_;
    float fieldValue_;
    
    FieldNode(int uuid, std::time_t timestamp, float fieldVal) : uuid_{uuid}, timestamp_{timestamp}, fieldValue_{fieldVal}{
        
    }
};

#endif /* FieldNode_h */
