#ifndef PARSER
#define PARSER
#include <iostream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

class Parser{
public:
    Parser(string input) : command(input){}

    void store(string str);
    //HELPER FUNCTIONS
    void print();


private:
    vector<const char*> container;
    string command; //use command.c_str() to convert from string to char pointer
};

void Parser::print(){
    cout << "char* : " << command << endl;
}

void Parser::store(string str){
    //find the special characters
    //[1]# - Anything after the ‘#’ character will be a comment
        //if # take substring of everything behind it first
    //; - next command will always be executed
        //separate the string into smaller sub strings
    //&& - next command executes only if previous command is successful
        //separate the string into smaller sub strings
    //|| - next command executes only if previous command fails
        //separate the string into smaller sub strings



}

#endif // PARSER

