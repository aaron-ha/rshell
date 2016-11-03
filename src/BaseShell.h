#ifndef BASESHELL_H
#define BASESHELL_H
#include<vector>
class BaseShell{
   
    public: 
    bool successFlag = true; 
    virtual void execute() = 0; 
    
}; 
#endif