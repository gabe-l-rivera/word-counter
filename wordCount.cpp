#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include "hasher.h"

using namespace std;

/* Author: Gabe Rivera
 * Date: Mar. 24, 2020
 * Purpose: CS315 Programming Assignment 4 - Word Count
 * Bugs: None as far as I'm aware of (:
 */

hasher::hasher(){ //constructor 
        for(int i = 0; i < t_s; i++){
                HashTable[i] = new item;
                HashTable[i]->word = "";
                HashTable[i]->count = 0;
                HashTable[i]->next = NULL;
        }
}

void hasher::addItem(string word){
        int index = Hash(word); // word is hashed and stored in index
        for(int i = 0; i < t_s; i++){ // parse thru table
                item *ptr = HashTable[index]; //create pointer of index
                while(ptr!=NULL){
                         if(ptr->word.compare(word) == 0){ // words are equal and check if word "exists"
                                ptr->count+=1;
                                return;
                         }
                         ptr = ptr->next;
                }
        }

        if(HashTable[index]->word == ""){
                HashTable[index]->word = word;
                HashTable[index]->count = 1;
        }else{
                item *ptr = HashTable[index];
                item *n = new item;
                n->word = word;
                n->count = 1;
                n->next = NULL;
                while(ptr->next != NULL){
                        ptr = ptr->next;
                }
                ptr->next = n;
        }

}

int hasher::Hash(string key){
        int hasher = 0;
        int index;
        for(int i = 0; i < key.length(); i++){
                hasher+=(int)key[i];
        }
        index = hasher % t_s;
        return index;
}

void displayResult(vector<string> v1, vector<int>v2){
    for(int i = 0; i < v1.size(); i++){
         cout << v1[i]<< " " << v2[i] << endl;
    }
    cout << endl;
}

void hasher::sortVectors(vector<string> vect1, vector<int> vect2){
        for(int i = 0; i < t_s; i++){
                item *ptr = HashTable[i];
                if(ptr->word == ""){ // use for debugging purposes
                        //cout << "index " << i << " is empty." << endl;
                }else{
                        while(ptr!=NULL){
                                // populate vectors
                                vect1.push_back(ptr->word);
                                vect2.push_back(ptr->count);
                                ptr = ptr->next;
                        }
                }
        }

        // sorted by word (alphabetical order) START
        string tempStr;
        int tempInt;
        for(int i = 0; i < vect1.size()-1; i ++){
                        for(int j = i+1; j < vect1.size(); j++){
                                if(vect1[i] > vect1[j]){
                                        tempStr = vect1[i];
                                        vect1[i] = vect1[j];
                                        vect1[j] = tempStr;
                                        tempInt = vect2[i];
                                        vect2[i] = vect2[j];
                                        vect2[j] = tempInt;
                                }
                        }
                }
        displayResult(vect1,vect2); // display sorted by word
        // sorted by word (alphabetical order) END


        // sorted by decreasing number of occurrences (reverse numerical order)
        for(int i = 0; i < vect1.size()-1; i ++){
                        for(int j = i+1; j < vect1.size(); j++){
                                if(vect2[i] == vect2[j]){ // check for ties, and sort alphabetically 
                                        if(vect1[i] > vect1[j]){
                                                tempStr = vect1[i];
                                                vect1[i] = vect1[j];
                                                vect1[j] = tempStr;
                                                tempInt = vect2[i];
                                                vect2[i] = vect2[j];
                                                vect2[j] = tempInt;
                                        }
                                }

                                if(vect2[i] < vect2[j]){
                                        tempStr = vect1[i];
                                        vect1[i] = vect1[j];
                                        vect1[j] = tempStr;
                                        tempInt = vect2[i];
                                        vect2[i] = vect2[j];
                                        vect2[j] = tempInt;
                                }
                        }
        }
        displayResult(vect1,vect2); // display sorted by reverse numerical order
        // sorted by decreasing number of occurrences (reverse numerical order)
}


int main(int argc, char **argv) {

        hasher Hash;
        ifstream infile(argv[1]);
        istream_iterator<string> in{ infile }, end;
        int d = distance(in, end);
        //cout << "Word count: " << d << endl; // used to find table size

        ifstream file(argv[1]); // traverse through file and populate an array of the file's words
        string words[d]; // string array to hold words
        if(file.is_open()){
                for(int i = 0; i < d; ++i){
                        file >> words[i]; // populate word array
                }
        }
        for(int i = 0; i < d; i++){
                Hash.addItem(words[i]); // hash words in word array
        }
        vector<string> v1;
        vector<int> v2;
        Hash.sortVectors(v1,v2); // let the sorting function do its magic (;

        return 0;
}
