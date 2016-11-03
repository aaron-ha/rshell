#!/bin/sh

cd ..
ls

bin/rshell < Tests/multi_command1.txt
bin/rshell < Tests/multi_command2.txt