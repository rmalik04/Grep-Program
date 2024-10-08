/*
 *  stringProcessing.cpp
 *  Krish Savla and Ranvir Malik
 *  24 April, 2022
 *
 *  Comp 15 Project 3 - gerp
 *
 *  Implementation of the stringProcessing class. Defines the only member
 *  function of the class. 
 */

#include <string>
#include "stringProcessing.h"
#include <iostream>

using namespace std;


/*
Name: stripNonAlphaNum
Parameters: a string
Return value: a string
Purpose: remove any special characters from a string
Other information: n/a
*/
std::string stripNonAlphaNum(std::string s) {
    size_t i = 0, start = 0, end = 0;
    int counter = 0; // counts number of numbers or letters
    // gets the starting index
    while (i < s.length()) {
        // ascii values for digits, letters, or capital letters
        if (s[i] >= 48 and s[i] <= 57) {
            start = i;
            i = s.length(); // ends the loop
            counter++;
        }
        else if (s[i] >= 65 and s[i] <= 90) {
            start = i;
            i = s.length();
            counter++;
        }
        else if (s[i] >= 97 and s[i] <= 122) {
            start = i;
            i = s.length();
            counter++;
        }
        else 
            i++;
    }
    i = 0;
    // gets the ending index
    while (i < s.length()) {
        if ((s[i] >= 48 and s[i] <= 57)) {
            end = i;
        }
        else if (s[i] >= 65 and s[i] <= 90) {
            end = i;
        }
        else if (s[i] >= 97 and s[i] <= 122) {
            end = i;
        }
        i++;
    }
    // if only special characters
    if (counter == 0) {
        return "";
    }
    string s1 = "";
    for (size_t j = start; j <= end; j++) {
        s1 = s1 + s[j]; 
    }
    return s1;
}

