#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <cstdlib>
#include "hasher.h"
#include <bits/stdc++.h>

using namespace std;


hasher::hasher(){
    for(int i = 0; i < t_s; i++){
        HashTable[i] = new item;
        HashTable[i]->word = "NO WORD AVAILABLE";
        HashTable[i]->next = NULL;
    }
}

void hasher::addItem(string word){
    int index = Hash(word);
    if(HashTable[index]->word == "NO WORD AVAILABLE"){
        HashTable[index]->word = word;
        //HashTable[index]->count = count;
    }else{
        item *ptr = HashTable[index];
        item *n = new item;
        n->word = word;
        n->next = NULL;
        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        ptr->next = n;
    }
}

int hasher::numberOfItems(int index){
    int count = 0;
    if(HashTable[index]->word == "NO WORD AVAILABLE"){
        return count;
    }else{
        count +=1;
        item *ptr = HashTable[index];
        while(ptr->next != NULL){
            count+=1;
            ptr = ptr->next;
        }
    }
    
    return count;
}

void hasher::printTable(){
    int number;
    for(int i = 0; i < t_s; i++){
        if(HashTable[i]->word != "NO WORD AVAILABLE"){
            number = numberOfItems(i);
            cout << HashTable[i]->word << " " << number << endl;
        }
    }
}

int hasher::Hash(string key){
    int hasher = 0;
    int index;
    for(int i = 0; i < key.length(); i++){
        hasher+=(int)key[i];
        //cout << "hash = " << hasher << endl;
    }
    index = hasher % t_s;
    return index;
}

void hasher::createArrays(string arr1[], int arr2[], int d){
    for(int i = 0; i < d; i++){
        arr1[i] = HashTable[i]->word;
        arr2[i] = numberOfItems(i);
    }
}

void lexSort(string array[], int array2[], int size){
    string tempStr;
    int tempInt;
    for(int i = 0; i < size-1; i ++){
        for(int j = i+1; j < size; j++){
            if(array[i] > array[j]){
                tempStr = array[i];
                array[i] = array[j];
                array[j] = tempStr;
                tempInt = array2[i];
                array2[i] = array2[j];
                array2[j] = tempInt;
            }
        }
    }
    
}

void printArray(string arr[], int arr2[], int dist){
    for(int i = 0; i < dist; i+=1){
        if(arr[i] != "NO WORD AVAILABLE")
            cout << arr[i]<< " " << arr2[i] << endl;
    }
}

int main(int argc, char **argv) {
    
    hasher Hash;
    ifstream infile(argv[1]);
    istream_iterator<string> in{ infile }, end;
    int d = distance(in, end);
    cout << "Word count: " << d << endl;
    
    
    ifstream file(argv[1]);
    string words[d];
    int count[d];
    if(file.is_open()){
        for(int i = 0; i < d; ++i){
            file >> words[i];
        }
    }
    for(int i = 0; i < d; i++){
        Hash.addItem(words[i]);
    }
    //Hash.printTable();
    Hash.createArrays(words,count,d);
    lexSort(words,count,d);
    printArray(words,count,d);
    return 0;
}

