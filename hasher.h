#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

#ifndef HASHER_H
#define HASHER_H

class hasher{
    
private:
    static const int t_s = 363;
    
    struct item{
        string word;
        //int count; //int
        item* next;
    };
    
    item* HashTable[t_s];
public:
    hasher();
    int Hash(string key);
    void addItem(string name);
    int numberOfItems(int index);
    void printTable();
    void createArrays(string arr1[], int arr2[], int d);
    
};



#endif //HASHER_H
