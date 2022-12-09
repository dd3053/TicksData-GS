//
//  CommandExecutor.cpp
//  Cpp_Practice
//
//  Created by Devesh Devendra on 24/11/22.
//

#include <stdio.h>
#include <string>
#include "CommandExecutor.h"


    

void CommandExecutor::executeCommand(std::string& command, std::unique_ptr<IDataObj>& myDataObj){
    std::stringstream ss(command);
    std::string commandFirst;
    getline(ss, commandFirst, ' ');
    if (commandFirst == "tickfile"){
        std::string fileName;
        getline(ss, fileName, ' ');
        myDataObj->readFile(fileName);
    }else if(commandFirst == "print"){
        std::string tmpString;
        getline(ss, tmpString, ' ');
        std::time_t startTime = static_cast<std::time_t>(stoi(tmpString));
        getline(ss, tmpString, ' ');
        std::time_t endTime = static_cast<std::time_t>(stoi(tmpString));
        getline(ss, tmpString, ' ');
        myDataObj->print(startTime, endTime, tmpString);
    }else if(commandFirst == "product"){
        std::string tmpString;
        getline(ss, tmpString, ' ');
        std::time_t startTime= static_cast<std::time_t>(stoi(tmpString));
        getline(ss, tmpString, ' ');
        std::time_t endTime = static_cast<std::time_t>(stoi(tmpString));
        getline(ss, tmpString, ' ');
        std::string symbol = tmpString;
        getline(ss, tmpString, ' ');
        std::string field1 = tmpString;
        getline(ss, tmpString, ' ');
        std::string field2 = tmpString;
        myDataObj->product(startTime, endTime, symbol, field1, field2);
    }
}
