//
//  IDataObj.h
//  An abstarct class implemented by PrintODataObj and ProductODataObj
//  More optimised approach can be created by extending this class.
//

#ifndef IDataObj_h
#define IDataObj_h

class IDataObj{
public:
    virtual void readFile(std::string& fileName) = 0;
    virtual void print(time_t startTime, time_t endTime, std::string& symbol) = 0;
    virtual void product(time_t startTime, time_t endTime, std::string& symbol, std::string& field1, std::string& field2) = 0;
    virtual ~IDataObj(){}
};


#endif /* IDataObj_h */
