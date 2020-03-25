#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef HASHER_H
#define HASHER_H

class hasher{

private:
        static const int t_s = 363; //equal to number of words

        struct item{
                string word;
                int count;
                item* next;
        };

        item* HashTable[t_s];
public:
        hasher();
        int Hash(string key);
        void addItem(string name);
        void sortVectors(vector<string> vect1, vector<int> vect2);
};

#endif //HASHER_H
