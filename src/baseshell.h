#ifndef BASESHELL
#define BASESHELL

static int exitHit = 0;

class BaseShell{

public:
   
    //virtual function that the leaf and component node will inherit
    virtual void execute() = 0;
    

};

#endif // BASESHELL

