//
//  PrintODataObj.cpp
//  
//

#include "PrintODataObj.hpp"

void PrintODataObj::resetFile(){
    for(auto itr = myMap_.begin(); itr != myMap_.end(); ++itr){
        std::vector<PrintONode*>& tmpVec = itr->second;
        for(int i = 0; i < tmpVec.size(); ++i){
            delete tmpVec[i];
        }
    }
    myMap_.clear();
}
    
    std::size_t PrintODataObj::searchIndex(std::vector<PrintONode*>& myVec, std::time_t startTime){
        std::size_t startIndex = 0;
        std::size_t endIndex = myVec.size() - 1;
        std::size_t ans = myVec.size();
        while(startIndex <= endIndex){
            std::size_t mid = startIndex + (endIndex - startIndex)/2;
            if(myVec[mid]->timestamp >= startTime){
                ans = mid;
                if(mid == 0) break;
                endIndex = mid - 1;
            }else{
                startIndex = mid + 1;
            }
        }
        return ans;
    }
    
    std::string PrintODataObj::getSymbolName(std::string& inputString){
        std::stringstream ss(inputString);
        std::string tmpString;
        getline(ss, tmpString, ',');
        getline(ss, tmpString, ',');
        return tmpString;
    }
    

    void PrintODataObj::readFile(std::string& fileName){
        resetFile();
        std::ifstream myFile;
        myFile.open(fileName);
        if(myFile.is_open()){
            std::string tmpString;
            while(getline(myFile, tmpString)){
                PrintONode* tmpNode = new PrintONode(tmpString);
                myMap_[getSymbolName(tmpString)].push_back(tmpNode);
            }
            myFile.close();
        }
        
    }
    
    void PrintODataObj::print(time_t startTime, time_t endTime, std::string& symbolString){
        if(myMap_.find(symbolString) == myMap_.end()){
            std::cout << std::endl;
            return;
        }
        std::size_t index = searchIndex(myMap_[symbolString], startTime);
        std::vector<PrintONode*>& tmpVec = myMap_[symbolString];
        while(index < tmpVec.size() && tmpVec[index]->timestamp <= endTime){
            std::cout << *tmpVec[index] << std::endl;
            ++index;
        }
        
    }
    
    void PrintODataObj::product(time_t startTime, time_t endTime, std::string& symbolString, std::string& field1, std::string& field2){
        if(myMap_.find(symbolString) == myMap_.end()){
            std::cout << 0 << std::endl;
            return;
        }
        std::size_t index = searchIndex(myMap_[symbolString], startTime);
        std::vector<PrintONode*>& tmpVec = myMap_[symbolString];
        long double ans = 0;
        while(index < tmpVec.size() && tmpVec[index]->timestamp <= endTime){
            PrintONode* tmpNode = tmpVec[index];
            float f1 = 0;
            float f2 = 0;
            for(int i = 0; i < tmpNode->featureMap_.size(); ++i){
                if(field1 == tmpNode->featureMap_[i].first){
                    f1 = tmpNode->featureMap_[i].second;
                }
                if(field2 == tmpNode->featureMap_[i].first){
                    f2 = tmpNode->featureMap_[i].second;
                }
            }
            ans += f1*f2;
            ++index;
        }
        std::cout << ans << std::endl;
    }

