//
//  CommandExecutor.h
//  Description :
//  -------------
//  1. Takes the Command as String and executes it on the dataObject.
//  2. Permissible Commands :
//      (i) tickfile <fileName>
//      (ii) print <startTime> <endTime> <symbol>
//      (iii) product <startTime> <endTime> <symbol> <field1> <field2>
//
//





#ifndef CommandExecutor_h
#define CommandExecutor_h

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

class CommandExecutor{
public:
    void executeCommand(std::string& command, std::unique_ptr<IDataObj>& myDataObj);
};

#endif /* CommandExecutor_h */
