/*
 *  gerp.cpp
 *  Krish Savla and Ranvir Malik
 *  24 April, 2022
 *
 *  Comp 15 Project 3 - gerp
 *
 *  Implementation of the gerp class. Defines all public and private member
 *  functions of the class. 
 *  
 */

#include <iostream>
#include <vector>
#include "gerp1.h"
#include "FSTree.h"
#include <fstream>
#include <string>
#include <sstream>
#include "stringProcessing.h"
#include <cstdlib>

using namespace std;

/*
Name: gerp1 - Constructor
Parameters: a DirNode
Return value: nothing
Purpose: default constructor for gerp class, fills all vectors with
null/placeholder values and intializes the table size. It also
creates an FSTree with the directory inputted.
Other information: n/a
*/
gerp1::gerp1(DirNode *root) {
    // initialize table size 
    table_size = 59;
    // fill with placeholder values
    for (int i = 0; i < table_size; i++) {
        vector<FP> tempVar;
        variation temp {"", tempVar};
        words.push_back(temp);
    }
    vector<DirNode*> path;
    filePath(root, path, "");
    
}
/*
Name: gerp1 - Destructor
Parameters: nothing
Return value: nothing
Purpose: recycle any memory that was allocated by the program
Other information: n/a
*/
gerp1::~gerp1() {

}
/*
Name: hash_value 
Parameters: a string and an integer
Return value: a size_t value 
Purpose: gets the hash value of the lowercase version of the word read in
Other information: n/a
*/
size_t gerp1::hash_value(string s, int size) {
    return hash<string>{}(s) % size;
}
/*
Name: insert
Parameters: a string that represents the whole file path where the word is 
found 
Return value: nothing
Purpose: indexes the words in the hash table 
Other information: n/a
*/
void gerp1::insert(string path) {
    // input file
    ifstream input;
    // line number counter
    int count = 1;
    // load factor for expansion
    double loadfactor;
    input.open(path);
    string s = "", line = "", temp = "";
        // read through every word in every file
        while (getline(input, line)) {
            stringstream ss(line);
            filepaths.push_back(line);
            while (ss >> s) {
                s = stripNonAlphaNum(s);
                loadfactor = words_size / table_size;
                if (loadfactor >= 0.7 or words[table_size - 1].low != "") {
                    table_size = 2 * table_size;
                    vector<variation> new_words;
                    // initialize new vector
                    for (int i = 0; i < table_size; i++) {
                        vector<FP> tempVar;
                        variation temp1 {"", tempVar};
                        new_words.push_back(temp1);
                    }
                    for (int i = 0; i < table_size / 2; i++) {
                        if (words[i].low != "") {
                            int index = hash_value(words[i].low, table_size);
                            while (new_words[index].low != "") {
                                index++;
                            }
                            // make deep copy 
                            new_words[index].low = words[i].low;
                            new_words[index].alters = words[i].alters;
                        }
                    }
                    words = new_words;
                }
                // getting lowercase version
                string lowercase = toLowerCase(s);
                // getting filepath with line number
                stringstream sscount;
                sscount << count;
                temp = line;
                size_t index = hash_value(lowercase, table_size);
                // if the selected index is empty
                if (words[index].low == "") {
                    insert_empty(s, lowercase, index, count, path);
                }
                // if the word is already in the hash
                else if (words[index].low == lowercase) {
                    // checking if that specific variation exists
                    insert_var(s, temp, index, count, path);
                }
                // using linear probing to handle collisions
                else if (words[index].low != lowercase) {
                    int probeCounter = index + 1;
                    bool probeCondition = false; 
                    // searching for the next available index
                    while (!probeCondition) {
                        if (words[probeCounter].low == "") {
                            insert_empty(s, lowercase, probeCounter, 
                            count, path);
                            probeCondition = true;
                        }
                        // if matching a probed word
                        else if (words[probeCounter].low == lowercase) {
                            insert_var(s, temp, probeCounter, count, path);
                            probeCondition = true;
                        }
                        probeCounter++;
                    }
                }
                temp = path;
            }
            total_line_count++;
            count++;
        }
}
/*
Name: insert_empty
Parameters: a string with the original word, a string with the lowercase
            version of the word, a size_t value representing the index, an
            integer representing the line number, a string representing the
            filepath
Return value: nothing
Purpose: insert a word into the hash table where there is an empty value at
         index.
Other information: n/a
*/
void gerp1::insert_empty(string s, string lowercase, size_t index, 
int lineNumber, string path) {
    // adding the current sentence to the back of the external vector
    // creating a temporary struct
    FP tempFP = {s, total_line_count, lineNumber, path};
    vector<FP> tempAlters;
    tempAlters.push_back(tempFP);
    // setting the variation struct variables 
    words[index].low = lowercase;
    words[index].alters = tempAlters;
    words_size++;
}
/*
Name: conditionChecker
Parameters: a string with the original word, a string with the lowercase
            version of the word, a size_t value representing the index, an
            integer representing the line number, a string representing the 
            full line that the word is found on
Return value: true or false 
Purpose: checks to see if there is a duplicate filepath and line number 
indexed for the same word in the hash
Other information: n/a
*/
bool gerp1::conditionChecker(size_t index, string path, string s, 
int lineNumber, string temp) {
    // as we push at back, we go through the alters array from the back to 
    // save time as when we find the line number and file path we don't 
    // push at back, else we do
    for (int i = int (words[index].alters.size()) - 1; i >= 0; i--) {
        if (words[index].alters[i].filePath != path or 
        words[index].alters[i].lineNumber != lineNumber) {
            return false;
        }
        // checking if the exact same variation exists on the same line
        else if (words[index].alters[i].original == s) {
            if (filepaths[words[index].alters[i].location] == temp) {
                return true;
            }
        }
    }
    return false;
}
/*
Name: insert_var
Parameters: a string with the original word, a string with the file path
            a size_t value representing the index, an
            integer representing the line number, a string representing the 
            full line that the word is found on
Return value: nothing
Purpose: insert a word in the hash if the index has been filled with
         variations of the word
Other information: n/a
*/
void gerp1::insert_var(string s, string temp, size_t index, 
int lineNumber, string path) {
    bool condition1 = conditionChecker(index, path, s, lineNumber, temp);
    // if the line number and file path isn't the same, we push at back
    if (condition1 == false) {
        // inserts the certain struct in the alters vector
        FP tempFP = {s, total_line_count, lineNumber, path};
        words[index].alters.push_back(tempFP);
    }
}
/*
Name: filePath
Parameters: a DirNode, a vector of DirNodes, and a string
Return value: nothing
Purpose: Iterates through the FSTree and gets the filepath of every file in 
         in the tree.
Other information: n/a
*/
void gerp1::filePath(DirNode *dir, vector<DirNode*> &path, string s) {
    // if it is empty
    if (dir == nullptr) {
        return;
    }
    // if it has an item
    else {
        path.push_back(dir);
    }
    // if it has subdirectories, we iterate through all of them and call the
    // function on them recursively
    if (dir->hasSubDir()) {
        for (int i = 0; i < dir->numSubDirs(); i++) {
            filePath(dir->getSubDir(i), path, s);
        }
    }
    // this goes through all the files in a certain directory and sends them
    // to the insert function, which reads them in, one by one
    if (dir->hasFiles()) {
        for (int i = 0; i < dir->numFiles(); i++) {
            s = path[0]->getName();
            for (int j = 1; j < int (path.size()); j++) {
                s = s + "/" + path[j]->getName();
            }
            s = s + "/" + dir->getFile(i);
            insert(s);
            s = path[0]->getName();
        }
    }
    path.pop_back();
}
/*
Name: toLowerCase
Parameters: a string
Return value: a string
Purpose: converts a string into a lowercase version of the string 
Other information: n/a
*/
string gerp1::toLowerCase(string s) {
    string lowercase = s;
    // uses the ascii values to convert to lower case
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] >= 65 and s[i] <= 90) {
            lowercase[i] = (lowercase[i] + 32); 
        }
    }
    return lowercase;
}
/*
Name: commandLoop
Parameters: an istream and an output stream
Return value: nothing
Purpose: command loop for the program. Preforms a function based on the user's
         input
Other information: n/a
*/
void gerp1::commandLoop(istream &command, ofstream &output) {
    // query and word to search
    string query, word;
    while (commandCon == true) {
        // read in the word inputted
        cout << "Query? ";
        command >> query;
        // quits the program
        if (query == "@q" or query == "@quit") { 
            cout << "Goodbye! Thank you and have a nice day." << endl;
            commandCon = false;
            return;
        }
        // performs case insensitive search
        else if (query == "@i" or query == "@insensitive") {
            command >> word;
            // removes all special characters from the word
            word = stripNonAlphaNum(word);
            string word1 = word;
            word = toLowerCase(word);
            size_t index = hash_value(word, table_size);
            print_insensitive(index, word, word1, output);
            
        }
        // changes the output file of the program
        else if (query == "@f") {
            output.close();
            ofstream o;
            command >> word;
            // open and write to new output file
            openOrDie(o, word);
            commandLoop(cin, o);
        }
        // preform a case sensitive search
        else {
            // removes any special characters from the word
            query = stripNonAlphaNum(query);
            word = toLowerCase(query);
            size_t index = hash_value(word, table_size);
            print_variation(index, query, word, output);
        }
    }
}
/*
Name: print_insensitive
Parameters: a size_t value, two strings, and an ofstream
Return value: nothing
Purpose: prints the the file path and line where the inputted word appears for
         a case insensitive search
Other information: n/a
*/
void gerp1::print_insensitive(size_t index, string s, string s1, 
ofstream &output) {
    // accouting for probing
    while (words[index].low != s and int (index) < table_size) {
        index++;
    }
    // if it gets to the end and doesn't find the word
    if (int (index) >= table_size) {
        output << s1 << " Not Found." << endl;
        return;
    }
    if (words[index].low != s) {
        output << s1 << " Not Found." << endl;
        return;
    } 
    bool dupFound = false;
    for (int i = 0; i < int (words[index].alters.size()) - 1; i++) {
        string tracker = words[index].alters[i].filePath;
        int lineTracker = words[index].alters[i].lineNumber;
        // checks for duplicates by checkng the line and not printing if 
        // the next line is the same as the one before
        if (words[index].alters[i + 1].filePath == tracker and 
        words[index].alters[i + 1].lineNumber == lineTracker) {
            dupFound = true;
        }
        if (dupFound == false) {
            output << words[index].alters[i].filePath << ":" 
                 << words[index].alters[i].lineNumber << ": "
                 << filepaths[words[index].alters[i].location] << endl;
        }
        dupFound = false; 
    }
    int last = words[index].alters.size() - 1;
    output << words[index].alters[last].filePath << ":" 
           << words[index].alters[last].lineNumber << ": "
           << filepaths[words[index].alters[last].location] << endl;
}
/*
Name: print_variation
Parameters: a size_t value, two strings, and an ofstream
Return value: nothing
Purpose: prints the the file path and line where the inputted word appears for
a case sensitive search
Other information: n/a
*/
void gerp1::print_variation(size_t index, string s, string s1, 
ofstream &output) {
    // accouting for probing
    while (words[index].low != s1 and int (index) < table_size) {
        index++;
    }
    // if it gets to the end and doesn't find the word
    if (int (index) == table_size) {
        output << s1 << " Not Found. Try with @insensitive or @i." << endl;
        return;
    }
    if (words[index].low != s1) {
        output << s1 << " Not Found. Try with @insensitive or @i." << endl;
        return;
    }
    // printing in all occurences
    for (int i = 0; i < int (words[index].alters.size()); i++) {
        if (words[index].alters[i].original == s) {
            output << words[index].alters[i].filePath << ":" 
                 << words[index].alters[i].lineNumber << ": "
                 << filepaths[words[index].alters[i].location] << endl;
        }
    }
}

/*
Name: openOrDie
parameters: variable to open files and the name of the file to be opened
return value: none
purpose: checks if the files can be opened 
other information: will stop the program if files cannot be opened
*/
template <typename streamtype>
void gerp1::openOrDie(streamtype &stream, string file_name) {
    stream.open(file_name);
    if (not stream.is_open()) {
        abort ("Unable to open: " + file_name);
    }
}

/*
Name: openOrDie
parameters: the error message to be printed
return value: none
purpose: prints out the error message required and exits the program
other information: will stop the program when called
*/
void gerp1::abort(string error_message) {
    cerr << error_message << endl;
    exit(EXIT_FAILURE);
}
/*
Name: test_print
parameters: nothing
return value: none
purpose: used in testing to print all items indexed into the hash 
other information: n/a
*/
void gerp1::test_print() {
    for (int i = 0; i < int (filepaths.size()); i++) {
        cout << filepaths[i] << "index = " << i << endl;
    }
}