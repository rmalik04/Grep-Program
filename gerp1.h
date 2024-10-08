/*
 *  gerp1.h
 *  Krish Savla and Ranvir Malik
 *  24 April, 2022
 *
 *  Comp 15 Project 3 - gerp
 *
 *  Header file for gerp class. Declares all public and private member
 *  functions and any private member variables.
 *
 */


#ifndef GERP_1_H
#define GERP_1_H

#include <iostream>
#include <vector>
#include <list>
#include "FSTree.h"
#include "DirNode.h"
#include <fstream>
#include <sstream>
#include "stringProcessing.h"
#include <string>

using namespace std;



class gerp1 { 
public:
    // constructor and destructor
    gerp1(DirNode* root);
    ~gerp1();

    size_t hash_value(string s, int size);
    void insert(string path);
    void commandLoop(istream &command, ofstream &output);
    
    // function used in testing
    void test_print();

private:
    template <typename streamtype>
    void openOrDie(streamtype &stream, string file_name);
    void abort(string error_message);
    string toLowerCase(string s);
    int numItems();
    bool conditionChecker(size_t index, string path, string s, 
    int lineNumber, string temp);
    void insert_var(string s, string temp, size_t index, 
    int lineNumber, string path);
    void insert_empty(string s, string lowercase, size_t index, 
    int lineNumber, string path);
    void filePath(DirNode *dir, vector<DirNode*> &path, string s);
    void print_insensitive(size_t index, string s, string s1, 
    ofstream &output);
    void print_variation(size_t index, string s, string s1, ofstream &output);
    
    struct FP {
        string original;
        int location;
        int lineNumber;
        string filePath;
    };
    struct variation {
        string low;
        vector<FP> alters;
    };

    // private member variables
    vector<variation> words;
    int table_size;
    int words_size = 0;
    int total_line_count = 0;
    vector<string> filepaths;
    bool commandCon = true;
};

#endif