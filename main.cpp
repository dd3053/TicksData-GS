#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <map>
#include <ctime>
#include <utility>

#include "IDataObj.h"
#include "ProductODataObj.hpp"
#include "PrintODataObj.hpp"
#include "CommandExecutor.h"
#include "PrintONode.h"
#include "FieldNode.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        std::cout << "Correct Usage Print Optimised : ./main -Oprint" <<std::endl;
        std::cout << "Correct Usage Product Optimised : ./main -Oproduct" <<std::endl;
        return 0;
    }
    std::string printString = "-Oprint";
    std::string productString = "-Oproduct";
    std::unique_ptr<IDataObj> myDataObj;
    
    if(printString.compare(argv[1]) == 0){
        std::unique_ptr<IDataObj> tmpObj {new PrintODataObj()};
        myDataObj = std::move(tmpObj);
    }else if(productString.compare(argv[1]) == 0){
        std::unique_ptr<IDataObj> tmpObj {new ProductODataObj()};
        myDataObj = std::move(tmpObj);
    }else{
        std::cout << "Incorrect Flag" << std::endl;
        return 0;
    }
    
    CommandExecutor commandExecutor;
    std::string command;
    while(true){
        std::getline(std::cin, command);
        if(command == "Exit") break;
        commandExecutor.executeCommand(command, myDataObj);
        std::cout << "Command Executed " << std::endl;
    }
    return 0;
}


