#ifndef PARSER
#define PARSER
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include "Token.h"

using namespace std;

class Parser{
public:
    Parser(string input);
    //HELPER FUNCTIONS
    vector<string> divideString(string str);
    void standardize();
    void reverseStr();
    void cleanString();
    void printContainer();
    void printConnectors();
    int numWords(string str);
    vector<char> getChContainer();
    vector<Token*> cmdsToVector();

    const char** makePtArr(string str);
private:
    vector<string> strContainer;
    vector<char*> charContainer;
    string command;
    vector<char> connectorCont;
};
#endif // PARSER