//
//  ProductODataObj.cpp
//  Cpp_Practice
//
//  Created by Devesh Devendra on 24/11/22.
//

#include "ProductODataObj.hpp"
#include <queue>
#include <vector>
#include <functional>

    
    std::size_t ProductODataObj::searchIndex(std::vector<FieldNode*>& myVec, std::time_t startTime){
        std::size_t startIndex = 0;
        std::size_t endIndex = myVec.size() - 1;
        std::size_t ans = myVec.size();
        while(startIndex <= endIndex){
            std::size_t mid = startIndex + (endIndex - startIndex)/2;
            if(myVec[mid]->timestamp_ >= startTime){
                ans = mid;
                if(mid == 0) break;
                endIndex = mid - 1;
            }else{
                startIndex = mid + 1;
            }
        }
        return ans;
    }
    
    
    std::size_t ProductODataObj::searchIndex(std::vector<PrintONode*>& myVec, std::time_t startTime){
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
    
    void ProductODataObj::resetData(){
        this->counter_ = 0;
        this->fieldLookUpMap.clear();
        this->reverseFieldLookup.clear();
        this->symbolLookUpMap.clear();
        
        for(auto itr = symbolToFieldMap_.begin(); itr != symbolToFieldMap_.end(); itr++){
            for(int i = 0; i < itr->second.size(); ++i){
                for(int j = 0; j < itr->second[i].second.size(); j++){
                    delete itr->second[i].second[j];
                }
            }
        }
        
        this->symbolToFieldMap_.clear();
    }
    
    std::string ProductODataObj::getSymbolName(std::string& inputString){
        std::stringstream ss(inputString);
        std::string tmpString;
        getline(ss, tmpString, ',');
        getline(ss, tmpString, ',');
        return tmpString;
    }
    
    void ProductODataObj::readFile(std::string& fileName){
        resetData();
        std::ifstream myFile;
        myFile.open(fileName);
        if(myFile.is_open()){
            std::string tmpString;
            while(getline(myFile, tmpString)){
                PrintONode* tmpNode {new PrintONode(tmpString)};
                std::string symbolName = getSymbolName(tmpString);
                if(symbolLookUpMap.find(symbolName) == symbolLookUpMap.end()){
                    symbolLookUpMap[symbolName] = static_cast<int>(symbolLookUpMap.size());
                }
                int symbolIndex = symbolLookUpMap[symbolName];
                for(int i = 0; i < tmpNode->featureMap_.size(); ++i){
                    std::string fieldName = tmpNode->featureMap_[i].first;
                    float val = tmpNode->featureMap_[i].second;
                    if(fieldLookUpMap.find(fieldName) == fieldLookUpMap.end()){
                        fieldLookUpMap[fieldName] = static_cast<int>(fieldLookUpMap.size());
                        reverseFieldLookup[static_cast<int>(reverseFieldLookup.size())] = fieldName;
                    }
                    int fieldIndex = fieldLookUpMap[fieldName];
                    bool isAdded = false;
                    for(int i = 0; i < symbolToFieldMap_[symbolIndex].size(); i++){
                        std::pair<int, std::vector<FieldNode*>>& itrNode = symbolToFieldMap_[symbolIndex][i];
                        if(itrNode.first == fieldIndex){
                            itrNode.second.push_back(new FieldNode{counter_, tmpNode->timestamp, val});
                            isAdded = true;
                            break;
                        }
                    }
                    if(!isAdded){
                        std::vector<FieldNode*> tmpVec;
                        tmpVec.push_back(new FieldNode{counter_, tmpNode->timestamp, val});
                        symbolToFieldMap_[symbolIndex].push_back({fieldIndex, tmpVec});
                    }
                }
                delete tmpNode;
                ++counter_;
            }
            myFile.close();
        }
    }
    
    
    void ProductODataObj::print(time_t startTime, time_t endTime, std::string& symbolString){
        if(symbolLookUpMap.find(symbolString) == symbolLookUpMap.end()){
            std::cout << std::endl;
            return;
        }
        int symbolIndex = symbolLookUpMap[symbolString];
        std::vector<int> tmpIndexer;
        std::priority_queue<int, std::vector<int>, std::greater<int>> minPQ;
        for(int i = 0; i < symbolToFieldMap_[symbolIndex].size(); ++i){
            std::vector<FieldNode*>& itrNode = symbolToFieldMap_[symbolIndex][i].second;
            int searchIndexer = static_cast<int>(searchIndex(itrNode, startTime));
            tmpIndexer.push_back(searchIndexer);
            if(searchIndexer < itrNode.size() && itrNode[searchIndexer]->timestamp_ <= endTime){
                minPQ.push(itrNode[searchIndexer]->uuid_);
            }
        }
        
        while(!minPQ.empty()){
            int minUUID = minPQ.top();
            //Remove all entries :
            while(!minPQ.empty() && minPQ.top() == minUUID){
                minPQ.pop();
            }
            for(int i = 0; i < tmpIndexer.size(); ++i){
                std::vector<FieldNode*>& itrNode = symbolToFieldMap_[symbolIndex][i].second;
                if(tmpIndexer[i] < itrNode.size() && itrNode[tmpIndexer[i]]->uuid_ == minUUID){
                    std::cout << reverseFieldLookup[symbolToFieldMap_[symbolIndex][i].first] << ":" << itrNode[tmpIndexer[i]]->fieldValue_ << std::endl;
                    ++tmpIndexer[i];
                    if(tmpIndexer[i] < itrNode.size() && itrNode[tmpIndexer[i]]->timestamp_ <= endTime){
                        minPQ.push(itrNode[tmpIndexer[i]]->uuid_);
                    }
                }
            }
            std::cout << std::endl;
        }
        
        
    }
    
    
    void ProductODataObj::product(time_t startTime, time_t endTime, std::string& symbolString, std::string& field1, std::string& field2){
        
        long double ans = 0;
        //Need to fetch the two Vectors :
        if(symbolLookUpMap.find(symbolString) == symbolLookUpMap.end()){
            std::cout << 0 << std::endl;
            return;
        }
        if(fieldLookUpMap.find(field1) == fieldLookUpMap.end()){
            std::cout << 0 << std::endl;
            return;
        }
        if(fieldLookUpMap.find(field2) == fieldLookUpMap.end()){
            std::cout << 0 << std::endl;
            return;
        }
        
        int symbolIndex = symbolLookUpMap[symbolString];
        int field1Index = fieldLookUpMap[field1];
        int field2Index = fieldLookUpMap[field2];
        std::vector<FieldNode*>* field1_Vec = nullptr;
        std::vector<FieldNode*>* field2_Vec = nullptr;
        for(int i = 0; i < symbolToFieldMap_[symbolIndex].size(); ++i){
            std::pair<int, std::vector<FieldNode*>>& tmpPair = symbolToFieldMap_[symbolIndex][i];
            if(tmpPair.first == field1Index){
                field1_Vec = &tmpPair.second;
            }
            if(tmpPair.first == field2Index){
                field2_Vec = &tmpPair.second;
            }
        }
        
        
        if(field1_Vec == nullptr || field2_Vec == nullptr){
            std::cout << 0 << std::endl;
            return;
        }
        
        std::size_t index1 = searchIndex(*field1_Vec, startTime);
        std::size_t index2 = searchIndex(*field2_Vec, startTime);
        
        while(index1 < field1_Vec->size() && index2 < field2_Vec->size()){
            if((*field1_Vec)[index1]->timestamp_ > endTime){
                break;
            }
            if((*field2_Vec)[index2]->timestamp_ > endTime){
                break;
            }
            if((*field1_Vec)[index1]->uuid_ == (*field2_Vec)[index2]->uuid_){
                ans += (*field1_Vec)[index1]->fieldValue_ * (*field2_Vec)[index2]->fieldValue_;
                ++index1;
                ++index2;
            }else if((*field1_Vec)[index1]->uuid_ < (*field2_Vec)[index2]->uuid_){
                ++index1;
            }else{
                ++index2;
            }
            
        }
        
        std::cout << ans << std::endl;
    }
