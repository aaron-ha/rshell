#ifndef PARSER
#define PARSER
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

class Parser{
public:
    Parser(string input) : command(input){}

    void store();
    void store(string str);

    //HELPER FUNCTIONS
    void print();


private:
    vector<string> strContainer;
    string command;
};

void Parser::print(){
//    cout << endl << strContainer.at(0) << endl;
    for(size_t i = 0; i < strContainer.size(); i++){
        cout << i << ": " << strContainer.at(i) << endl;
    }
}

void Parser::store(){
    store(command);
}

void Parser::store(string str){
    //remove spaces
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
    cout << "new str: " << str << endl;
    size_t found = str.find_first_of("#;&|");       // Here we want to check for multiple commands

    string newStr;

    if(found != string::npos){                                         //if found we want to find which commands
        size_t pos_hash = str.find_first_of("#");
        if(pos_hash != string::npos){
            cout << "pos_hash: " << pos_hash << endl;
            store(str.substr(0,pos_hash));
        }

        size_t pos_semi = str.find_first_of(";");
        if(pos_semi != string::npos){
            cout << "pos_semi: " << pos_semi << endl;
            store(str.substr(0,pos_semi));
        }

        size_t pos_and = str.find_first_of("&");
        if(pos_and != string::npos){
            cout << "pos_and: " << pos_and << endl;
            store(str.substr(0,pos_and));
        }

        size_t pos_or = str.find_first_of("|");
        if(pos_or != string::npos){
            cout << "pos_or: " << pos_or << endl;
            store(str.substr(0,pos_or));
        }
    }
    else{                                               //if not just push the string to the vector
        cout << "Not found, will now push \"" << str << "\" to vector";
        strContainer.push_back(str);
    }

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

