Execution : 
-------------

- To compile the program, Execute the following Command : `g++ -g -std=c++17 *.cpp -o output`
- To run the program in Print Optimised Mode : `./output -Oprint`
- To run the program in Product Optimised Mode : `./output -Oproduct`
- The Command Line Argument should be always present and thus the program can run in either Print Optimised or Product Optimised Mode.


Commands :
--------------
1. tickfile <fileName> : Reads the tick file from the given location. The program assumes that the file is always valid.

2. print <startTime> <endTime> <Symbol> : Prints the Symbol with `timestamp >= startTime and timestamp <= endTime`. The Symbol may or may not be present in the file. If symbol is not present an empty line is printed. The program assumes that the startTime >= endTime and they are non-negative.

3. product <startTime> <endTime> <Symbol> <FieldName1> <FieldName2> : Prints the sum of the product of `field1Value*field2Value` for a given Symbol and the corresponding FieldValues.

**Note : The tickfile command takes considerable time. After sucessful execution of a command, `Command Executed` gets displayed.**


Approach :
---------------
1. Optimisations for Print Optimisation Mode : 
    -   Stores the Data in unordered_map. The Key is the SymbolName. The value is the vector of PrintONode(which has timestamp and all the features stored).
    -   As the data comes in non-decreasing order, the vector for the SymbolName is located and the new data is appended at the tail of the vector.
    -   For print operations, the index of the first PrintONode is located which has timestamp >= startTime. The vector is iterated and every PrintONode is printed in the CommandLine. This approach is used as all the PrintONode need to be printed for a particular Symbol in the given timerange. Vector allows faster insertion operations.
    -   For product operations, the index is located similarly as above. The entire vector is iterated and the product for the both field values is calculated. 

2. Optimisations for Product Optimsation Mode : 
    -   Stores the data in an unordered_map where key is the SymbolName. The value corresponds to a vector of pairs, where each pair has fieldID as key and vector of FieldNode as value. The fieldNode contains three fields :
        -   `uuid_` : This helps to differentiate between two rows if two rows have the same timestamp.
        -   `timestamp` : The timestamp of the row.
        -   `Field Value` : The value of a particular Field.
        
    - The printing is done by identifying the index of every field for a given symbol such that the timestamp >= startTime. A minimum PriorityQueue is kept to keep track of the minimum uuid seen.All the fields belonging to this minimum uuid is printed and the next uuid from each field are inserted. 
    
    - For product of two fields : 
        - Use binary search to locate the index of the two FieldNodes of the required fields such that timestamp >= startTime
        - If both the FieldNodes have the same uuid, then they belong to the same tick and are considered for the calculation.
        - Otherwise, the index of the FieldNode with minimum uuid is incremented.
        - This is very beneficial while querying fields which are less occuring as it only traverses the Tick Data which have the given field.
        - Another possible way would be store the result of all possible queries, which would give the results very fast however it would consume a lot of Memory Space.
        - Representation for DataStructure : 
            SYM --> Field1 --> [All FieldNode(FieldValue, timestamp, uuid) having  Field1]
                    Field2 --> [All FieldNode having the values of Field2]
                    Field3 --> [All FieldNode having the values of Field3]
        
    - To save the memory, instead of storing the fieldname as string in every Symbol, a lookUp Map is sued which converts a given field Name to an int value.
        
    

