#ifndef BASESHELL_H
#define BASESHELL_H
#include<vector>
class BaseShell{
   
    public: 
    int successFlag;  
    virtual void execute() = 0; 
    
}; 
#endif