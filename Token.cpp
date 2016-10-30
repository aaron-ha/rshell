#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


  //int execute(char const* comman[]){  
  int main(){
    pid_t pid;
    pid_t waitid; 
    int status; 
    char const** command  = {"ls", "-a", NULL};
    
    //forks into two processes 
    pid = fork();
    //There was an error during fork
    if (pid < 0) 
    {
       perror("There was an error");
    } 
    else if (pid == 0) 
    {
     //must be cast because our function expects a char *const argv[]
     if (execvp(command[0], (char**)command) < 0) 
     { 
        //error at execvp
       perror("There was an error executing the process");
     }
     exit(EXIT_FAILURE);
   } 
  //forking was sucessful, go to parent process and wait for child to complete.
  else 
  {
    do 
    {
      waitid = waitpid(pid, &status, WUNTRACED | WCONTINUED);
      if(waitid == -1){
          perror("Waitpid")
          exit(EXIT_FAILURE);
      }
    } 
    //when child exits or ternimated by signal call stop waiting
    while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
    
  }
    