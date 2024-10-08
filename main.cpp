/*
 *  main.cpp
 *  Krish Savla and Ranvir Malik
 *  24 April, 2022
 *
 *  Comp 15 Project 3 - gerp
 *
 *  Driver file of the gerp class. Instructs the program on how to run by 
 *  opening the output file and starting the command loop.
 *  
 */

#include <iostream>
#include <vector>
#include "gerp1.h"
#include "FSTree.h"
#include <fstream>
#include <string>

using namespace std;

template <typename streamtype>
void openOrDie(streamtype &stream, string file_name);
void abort(string error_message);

int main (int argc, char *argv[]) {
    // if there are too many or too few inputs in the input line
    if (argc != 3) {
        cerr << "Usage: ./the_gerp inputDirectory outputFile" << endl;
        return 0;
    }
    // take in the name of the directory from command line
    string directoryName = argv[1];
    // create FSTree from directory inputted
    FSTree directory(directoryName);
    // get name of output file
    string outputFile = argv[2];
    // prepare output file to write to
    ofstream o;
    openOrDie(o, outputFile);
    // create gerp class and start command loop
    gerp1 g(directory.getRoot());
    g.commandLoop(cin, o);
    // g.test_print();
    o.close();
    return 0;
}

/*
parameters: variable to open files and the name of the file to be opened
return value: none
purpose: checks if the files can be opened 
other information: will stop the program if files cannot be opened
*/
template <typename streamtype>
void openOrDie(streamtype &stream, string file_name) {
    stream.open(file_name);
    if (not stream.is_open()) {
        abort ("Unable to open: " + file_name);
    }
}

/*
parameters: the error message to be printed
return value: none
purpose: prints out the error message required and exits the program
other information: will stop the program when called
*/
void abort(string error_message) {
    cerr << error_message << endl;
    exit(EXIT_FAILURE);
}