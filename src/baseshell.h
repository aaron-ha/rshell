#ifndef BASESHELL
#define BASESHELL

class BaseShell{

public:
    BaseShell() : successFlag(true){};
    //this flag will keep track of the result of the execution
    bool successFlag;
    //virtual function that the leaf and component node will inherit
    virtual void execute() = 0;
    //Will be used by the token class to hold the command
    //

};

#endif // BASESHELL

