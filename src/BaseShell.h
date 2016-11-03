#ifndef BASESHELL
#define BASESHELL

class BaseShell{

public:
    bool successFlag = true;
    virtual void execute() = 0;
    const char** command; 

};

#endif // BASESHELL

