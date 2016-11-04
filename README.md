#CS100 Assignment 2 - rshell

###Elijah Cain and Aaron Ha

## Summary and Requirements
This is a c++ program that acts as a BASH Shell. It has the capability to execute all bash commands
found in bin so it cannot do commands such as ```cd```. It also has the capabilty of handling mutliple commands using 
the BASH connectors ```||```, ```&&``` and ```;```. If the user enters `#` it will act as a comment and everything after it will be ignored. These connectors will determing if the command is executed based off
of the previous commands success. The program will exit when the user hits "exit". 

##Developer Tasks 
Aaron was tasked with parsing the user input and storing it into a container, and Elijah was responsible for handling execution as well as general program organization. We developed entirely on c9.io and cloned the repo into the service so that we could push updates onto our remote repo. This is the reason why only one person commited to the repository. 

##Strategy
A composite pattern was used a with one leaf node and one composite node. A indivdual command was encapsualted in a `Token` leaf node and the `TokenComposite` node has a container of `Token` nodes. The base class has a `execute` function that the children implemented. `Token`'s `execute()` would have the system calls `fork()` and `execvp()` to execute the indivdual programs. The `TokenComposite`'s `execute()` would iterate through the `Token` objects in it's container and call `execute` on the leaf nodes. The `Parser` class was responsible for parsing the user input and populating the `Token` objects and `TokenComposite` container.  
## Bugs
Sometimes the commands would not behave as expected. An example would be putting a command like `-ls -apple` . When attempting to use the command "ls -apples" for example, the code does not flag an error (only when tested outside of hammer)
instead it will list all the information of every file.

When running the scripts the script would sometimes go under an infinite loop (I believe this is because we didn't call exit, aside from exit test cases)

Comparison between ints and size_types would cause occasional parse bugs. 

GNU GENERAL PUBLIC LICENSE
