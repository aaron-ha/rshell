#include "token.h"
Token::Token(){}

Token::Token(const char** argv) { //take in parsed argument 
    command = argv; 
}

//this will execute the program using fork and execvp
void Token::execute(){
    pid_t pid;
    pid_t waitId;
    int status;
    
    
    if(strcmp(command[0], "test") == 0 || strcmp(command[0], "[") == 0){
        test(command); 
    }
    else{
        //forks into two processes
        pid = fork();
        
        //There was an error during fork
        if (pid < 0){
    
            perror("There was an error");
        }
        else if (pid == 0){
            //must be cast because our function expects a char *const argv[]
            if (execvp(command[0], (char**)command)  < 0){
                //error at execvp
                perror("There was an error executing the process");
            }
            exit(EXIT_FAILURE);
        }
        //forking was sucessful, go to parent process and wait for child to complete.
        else{
            do{
                waitId = wait(&status);
                if(status != 0){ //if the status is not zero, then the user entered an invalid argument
                    successFlag = false;
                }
                if(waitId == -1){
                    perror("Error in parent process");
                    exit(EXIT_FAILURE);
                }
            }
            //when child exits or ternimated by signal call stop waiting
            while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }
    
}

void Token::test(const char** command){
    struct stat sb; 
    
    int sizeOfCommand = 0;  
    for(int i = 0; command[i]!= NULL; i++){
        sizeOfCommand++; 
    }
    
    if(strcmp(command[0], "[") == 0 && strcmp(command[sizeOfCommand-1], "]") != 0){
        std::cout << "bash: [: missing ']" << std::endl;
    }
    else if(strcmp(command[1], "-e") == 0){
        if (stat(command[2], &sb) == -1) {
            std::cout << "(False)" << std::endl; 
            successFlag = false;
            perror("File Status:");
        }
        else{
            std::cout << "(True)" << std::endl; 
        }
        
    }
    else if(strcmp(command[1], "-f" ) == 0){
        if (stat(command[2], &sb) == -1) {
            std::cout << "(False)" << std::endl; 
            successFlag = false;
            perror("File Status:");
        }
        else if(S_ISREG(sb.st_mode)){
            std::cout << "(True)" << std::endl; 
        }
        else{
            std::cout << "(False)" << std::endl; 
        }

    }
    else if(strcmp(command[1], "-d" ) == 0){
        if (stat(command[2], &sb) == -1) {
            std::cout << "(False)" << std::endl; 
            successFlag = false;
            perror("File Status:");
            
        }
        else if(S_ISDIR(sb.st_mode)){
            std::cout << "(True)" << std::endl; 
        }
        else{
            std::cout << "(False)" << std::endl; 
        }
       
    }
    else{
      if (stat(command[1], &sb) == -1) {
            std::cout << "(False)" << std::endl; 
            successFlag = false;
            perror("File Status:");
            
        }
        else{
           std:: cout << "(True)" << std::endl; 
        }
    }
}
