#!/bin/sh

cd ..

bin/rshell < Tests/exit.txt
echo
bin/rshell < Tests/multi_exit1.txt
