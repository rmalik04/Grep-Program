/*
 *  unit_tests.h
 *  Krish Savla and Ranvir Malik
 *  24 April, 2022
 *
 *  Comp 15 Project 3 - gerp
 *
 *  Testing file for the stringProcessing class with different scenarios
 *  of strings and the toLowercase member function from the gerp class.
 */
 
#include <cassert>
#include "stringProcessing.h"
#include "gerp.h"
#include <string>

using namespace std;
// test the stripNonAlphaNum function on a string with no special characters
void string1() {
    string s = "abc";
    cout << s << endl;
    string s1 = stripNonAlphaNum(s);
    cout << s1 << endl;
    assert(s1 == "abc");
}
// test the stripNonAlphaNum function on a string with special characters
void string2() {
    string s = ";;;[];44abc[[];8a;;;";
    cout << s << endl;
    string s1 = stripNonAlphaNum(s);
    cout << s1 << endl;
    assert(s1 == "44abc[[];8a");
}
// test the stripNonAlphaNum function on a string with other special characters
void string3() {
    string s = "@##!!#!@!#COMP-15!!!!!!!";
    cout << s << endl;
    string s1 = stripNonAlphaNum(s);
    cout << s1 << endl;
    assert(s1 == "COMP-15");
}
// test on a string with only special values
void string4() {
    string s = "{.....";
    cout << s << endl;
    string s1 = stripNonAlphaNum(s);
    cout << s1 << endl;
    assert(s1 == "");
}
// test on a string with only one letter
void string5() {
    string s = "q";
    cout << s << endl;
    string s1 = stripNonAlphaNum(s);
    cout << s1 << endl;
    assert(s1 == "q");
}
// to test toLowerCase from gerp
void tolower() {
    string s ="DoG";
    string lowercase = s;
    // this is the code we used in our toLowerCase function, 
    // since it was private we copied over the code so we didn't
    // have to comment it out
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] >= 65 and s[i] <= 90) {
            lowercase[i] = (lowercase[i] + 32); 
        }
    }
    assert("dog" == lowercase);
}
// test the to lower function on a string with all capital letters
void tolower1() {
    string s ="ABCD";
    string lowercase = s;
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] >= 65 and s[i] <= 90) {
            lowercase[i] = (lowercase[i] + 32); 
        }
    }
    assert("abcd" == lowercase);
}

