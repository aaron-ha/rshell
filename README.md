#CS100 Assignment 2

## Summary
This is a c++ program that acts as a BASH Shell. It has the capability to execute all bash commands
found in bin so it cannot do commands such as ```cd```. It also has the capabilty of handling mutliple commands using 
the BASH connectors ```||```, ```&&``` and ```;```. These connectors will determing if the command is executed based off
of the previous commands success. The program will exit when the user hits "exit". 



## Bugs
When attempting to use the command "ls -apples" for example. The code does not flag an error (only when tested outside of hammer)
instead it will list all the information of every file

When running the scripts the script would sometimes go under an infinite loop (I believe this is because we didn't call exit, aside from exit test cases)

Sometimes the commands would not behave as expected

Comparison between ints and size_types