#include "parser.h"

//Parse function:
//Parse breaks down the user inputted string by calling the divideString function
void Parser::parse(string cmd){
    this->divideString(cmd);
}
//OLD---------------------------------------------------------------------------------------------------
// //Getter for the connector container
// vector<char> Parser::getChContainer(){
//     return connectorCont;
// }

// //Commands To Vector function:
// //cmdsToVector calls the makePtArr function for every element in the vector<string> container
// //then returns a new vector of tokens
// vector<Token*> Parser::cmdsToVector(){
//     vector<Token*> listOfCmds;
//     Token* tk;
//     for(unsigned int i = 0; i < strContainer.size(); i++){
//         tk = new Token(makePtArr(strContainer.at(i)));
//         listOfCmds.push_back(tk);
//     }
//     return listOfCmds;
// }
//OLD----------------------------------------------------------------------------------------------------------------

//NEW----------------------------------------------------------------------------------------------------------------
//Getter for the connector container
vector<char> Parser::getChContainer(){
    vector<char> newCont;
    for(unsigned int i = 0; i < connectorCont.size(); i++){
        if (connectorCont[i] == '(')
            while(connectorCont[i] != ')')
                i++;
        else
            newCont.push_back(connectorCont[i]);
    }
    return newCont;
}

bool Parser::checkForParenthesis(vector<char> myVector){
    for(unsigned i = 0; i < myVector.size(); i++)
        if (myVector[i] == '(')
            return true;
    return false;
}

//Commands To Vector function:
//cmdsToVector calls the makePtArr function for every element in the vector<string> container
//then returns a new vector of tokens
vector<Token*> Parser::cmdsToVector(){
    vector<Token*> listOfCmds;
    Token* tk;

    if(checkForParenthesis(connectorCont) == false){
        for(unsigned int i = 0; i < strContainer.size(); i++){
            tk = new Token(makePtArr(strContainer.at(i)));
            listOfCmds.push_back(tk);
        }
    }
    else{
        int currentToken = 0;

        for(int i = 0; i < connectorCont.size(); i++){
            if(connectorCont[i] == '('){
                i++;
                tk = new Token();
                while(connectorCont[i] != ')'){
                    tk->connectors.push_back(connectorCont[i]);
                    tk->tokens.push_back(makePtArr(strContainer.at(currentToken)));
                    currentToken++;
                    i++;
                }
                tk->tokens.push_back(makePtArr(strContainer.at(currentToken)));
                currentToken++;
                listOfCmds.push_back(tk);
            }
            else{
                if((connectorCont[i+1] != '(') && (connectorCont[i-1] != ')')){
                    tk = new Token(makePtArr(strContainer.at(currentToken)));;
                    currentToken++;
                    listOfCmds.push_back(tk);                    
                }
            }

        }
    }
    return listOfCmds;
}

//NEW----------------------------------------------------------------------------------------------------------------
//make an Array of pointers function:
//makePtArr takes a string and turns it into a character array pointer by
//separating words from a string by using the space as a delimeter
//after the word is separated, it'll be make into a character pointer and stored into the array of character pointers
const char** Parser::makePtArr(string str){
    int wordCount = numWords(str);

    const char** list = new const char*[wordCount+1];
    char* cpy;
    string newStr = str;


    for(int i = 0; i < wordCount; i++){
        for(unsigned int j = 0; j < newStr.length(); j++)
            if(newStr[j] == ' '){                                //Separating the command by breaking them down into pointers
                cpy = new char[j+1];                             //Make a new pointer of j+1 size
                strcpy(cpy,  newStr.substr(0, j).c_str());       //Use strcpy to store the converted sub-string by using c_str
                list[i] = cpy;                                   //Store that const char* pointer into the character pointer array
                newStr = newStr.substr(j+1, newStr.length());    //Create a substring of the remaining string
                j = newStr.length();                             //break out of the inner for loop
            }
    }
    cpy = new char[newStr.length()];                             //Add the last command into the char pointer array
    strcpy(cpy,  newStr.c_str());
    list[wordCount-1] = cpy;

    list[wordCount] = (const char*) '\0';                        //point the char* to the null terminating character

    return list;
}

//Prints the string container
void Parser::printContainer(){
    cout << "String Container: " << endl;
    for(size_t i = 0; i < strContainer.size(); i++)
        cout << i << ": " << strContainer.at(i) << endl;

}

//Prints the connector container
void Parser::printConnectors(){
    cout << "Connector Container: " << endl;
    for(size_t i = 0; i < connectorCont.size(); i++)
        cout << i << ":\t" << connectorCont.at(i) << endl;
}

//Divide String method:
//divideString breaks down the string by the connectors (;, &&, ||) making smaller strings of separate commands
//The pound (#) symbol will be truncated along with the comments following the symbol
//After making a vector of strings with each command, the function will be cleaned up by removing the spaces before and after
vector<string> Parser::divideString(string str){
    string newStr = str;

    size_t hash_found = str.find_first_of('#');             //truncates the string by shaving off the comments found after the pound symbol
    if(hash_found != string::npos){
        newStr = str.substr(0, hash_found);                 //creates a new string without the comments
    }

    for(unsigned int i = 0; i < newStr.length(); i++){
        if(newStr[i] == ';'){
            connectorCont.push_back(';');                   // ; will represent the ; connector
            strContainer.push_back(newStr.substr(0, i));
            newStr = newStr.substr(i+1, newStr.length());
            i = 0;
        }
        else if(newStr[i] == '&' && newStr[i+1] == '&'){    //Looks for "&&" within the string
            connectorCont.push_back('&');                   // & will represent the && connector
            strContainer.push_back(newStr.substr(0, i));
            newStr = newStr.substr(i+2, newStr.length());
            i = 0;
        }
        else if(newStr[i] == '|' && newStr[i+1] == '|'){    //Looks for "||" within the string
            connectorCont.push_back('|');                   // | will represent the || connector
            strContainer.push_back(newStr.substr(0, i));
            newStr = newStr.substr(i+2, newStr.length());
            i = 0;
        }
    }
    strContainer.push_back(newStr.substr(0, newStr.length()));
    standardize();                                          //cleans up the container
    return strContainer;
}

//Cleans the string by removing spaces.
void Parser::standardize(){
    cleanString();  //removes the spaces in front of the string
    reverseStr();   //Reverses the string
    cleanString();  //removes the spaces in front of the string... which is actually the back of the string.
    reverseStr();   //Return string to default construction
}

//Removes all unnecessary spaces found before the string.
void Parser::cleanString(){
    for(unsigned int i = 0; i < strContainer.size(); i++){
        for(unsigned int j = 0; j < strContainer.at(i).length(); j++){
            size_t notSpace = strContainer.at(i).find_first_not_of(" ");
            if(notSpace != string::npos){
                strContainer.at(i) = strContainer.at(i).substr(notSpace, strContainer.at(i).length());
            }
        }
    }
}

//Uses algorithm's library function reverse to reverse the string.
void Parser::reverseStr(){
    for(unsigned int i = 0; i < strContainer.size(); i++)
        reverse(strContainer.at(i).begin(), strContainer.at(i).end());
}

//Function determines the amount of words in the string
int Parser::numWords(string str){
    int count = 0;
    for(unsigned int i = 0; i < str.length(); i++)
        if(str[i] == ' ')
            count++;
    count+=1;
    return count;
}
