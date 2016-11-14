#include "token.h"

Token::Token(const char** argv) { //take in parsed argument 
    command = argv; 
}

//this will execute the program using fork and execvp
void Token::execute(){
    pid_t pid;
    pid_t waitId;
    int status;
    
    if(strcmp(command[0], "test") || strcmp(command[0], "[")){
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

void Token:test(){
    struct stat sb; 
    if(strcmp(command[1], "-e")){
        if (stat(argv[2], &sb) == -1) {
            perror("File Status:");
            exit(EXIT_FAILURE);
            std::cout << "(False)" << std::endl; 
            successFlag = false;
            exit(EXIT_FAILURE);
        }
           std:: cout << "(True)" << std::endl; 
    }
    else if(strcmp(command[1], "-f")){
        if (stat(argv[2], &sb) == -1) {
            perror("File Status:");
            exit(EXIT_FAILURE);
            std::cout << "(False)" << std::endl; 
            successFlag = false;
            exit(EXIT_FAILURE);
        }
        if(S_ISREG(sb.st_mode)){
            std::cout << "(True)" << std::endl; 
        }
        else{
            std::cout << "(False)" << std::endl; 
        }
    }
    else if(strcmp(command[1], "-d")){
        if (stat(argv[2], &sb) == -1) {
            perror("File Status:");
            exit(EXIT_FAILURE);
            std::cout << "(False)" << std::endl; 
            successFlag = false;
            exit(EXIT_FAILURE);
        }
        if(S_ISDIR(sb.st_mode)){
            std::cout << "(True)" << std::endl; 
        }
        else{
            std::cout << "(False)" << std::endl; 
        }
    }
    else{
      if (stat(argv[1], &sb) == -1) {
            perror("File Status:");
            exit(EXIT_FAILURE);
            std::cout << "(False)" << std::endl; 
            successFlag = false;
            exit(EXIT_FAILURE);
        }
           std:: cout << "(True)" << std::endl; 
    }
}
