#include "Parser.h"

Parser::Parser(string input) : command(input){}

vector<Token*> Parser::cmdsToVector(){
    vector<Token*> listOfCmds;
    Token* tk;
    for(int i = 0; i < strContainer.size(); i++){
//        cout << "token(makePtArr(strContainer.at(" << i<< ")):\t" << makePtArr(strContainer.at(i) << endl;
        tk = new Token(makePtArr(strContainer.at(i)));
        listOfCmds.push_back(tk);
    }
    return listOfCmds;
}

vector<char> Parser::getChContainer(){
    return connectorCont;
}

const char** Parser::makePtArr(string str){
    int wordCount = numWords(str);

    const char** list = new const char*[wordCount];

    char* cpy;
    string newStr = str;

    for(int i = 0; i < wordCount; i++){
        for(int j = 0; j < newStr.length(); j++)
            if(newStr[j] == ' '){
                cpy = new char[j+1];
                strcpy(cpy,  newStr.substr(0, j).c_str());
                list[i] = cpy;
                newStr = newStr.substr(j+1, newStr.length());
                j = newStr.length();
            }
    }
    newStr.append("\0");
    cpy = new char[newStr.length()];
    strcpy(cpy,  newStr.c_str());
    list[wordCount-1] = cpy;

    for(int x = 0; x < wordCount; x++){
        cout << "list[" <<  x << "]:\t" << list[x] << endl;
    }
    return list;
}

void Parser::printContainer(){
    cout << "String Container: " << endl;
    for(size_t i = 0; i < strContainer.size(); i++)
        cout << i << ": " << strContainer.at(i) << endl;

}

void Parser::printConnectors(){
    cout << "Connector Container: " << endl;
    for(size_t i = 0; i < connectorCont.size(); i++)
        cout << i << ":\t" << connectorCont.at(i) << endl;
}

vector<string> Parser::divideString(string str){
    string newStr = str;

    size_t hash_found = str.find_first_of('#');
    if(hash_found != string::npos){
        newStr = str.substr(0, hash_found);
    }

    cout << "newStr: " << newStr << endl;

    for(int i = 0; i < newStr.length(); i++){
        if(newStr[i] == ';'){
            connectorCont.push_back(';');
            strContainer.push_back(newStr.substr(0, i));
            newStr = newStr.substr(i+1, newStr.length());
            i = 0;
        }
        else if(newStr[i] == '&' && newStr[i+1] == '&'){
            connectorCont.push_back('&');
            strContainer.push_back(newStr.substr(0, i));
            newStr = newStr.substr(i+2, newStr.length());
            i = 0;
        }
        else if(newStr[i] == '|' && newStr[i+1] == '|'){
            connectorCont.push_back('|');
            strContainer.push_back(newStr.substr(0, i));
            newStr = newStr.substr(i+2, newStr.length());
            i = 0;
        }
    }
    strContainer.push_back(newStr.substr(0, newStr.length()));
    standardize();
    return strContainer;
}

void Parser::standardize(){
    cleanString();
    reverseStr();
    cleanString();
    reverseStr();
}

void Parser::cleanString(){
    for(int i = 0; i < strContainer.size(); i++){
        for(int j = 0; j < strContainer.at(i).length(); j++){
            size_t notSpace = strContainer.at(i).find_first_not_of(" ");
            if(notSpace != string::npos){
                strContainer.at(i) = strContainer.at(i).substr(notSpace, strContainer.at(i).length());
            }
        }
    }
}

void Parser::reverseStr(){
    for(int i = 0; i < strContainer.size(); i++)
        reverse(strContainer.at(i).begin(), strContainer.at(i).end());
}

int Parser::numWords(string str){
    int count = 0;
    for(int i = 0; i < str.length(); i++)
        if(str[i] == ' ')
            count++;
    count+=1;
    return count;
}
