#ifndef PARSER
#define PARSER
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include "token.h"

using namespace std;

class Parser{
public:
    Parser(){};

    void parse(string cmd);

    vector<Token*> cmdsToVector();
    vector<char> getChContainer();

    //HELPER FUNCTIONS
    void printContainer();
    void printConnectors();
private:
    vector<string> strContainer;
    string command;
    vector<char> connectorCont;

    const char** makePtArr(string str);
    vector<string> divideString(string str);
    void standardize();
    void reverseStr();
    void cleanString();
    int numWords(string str);
};
#endif // PARSER
