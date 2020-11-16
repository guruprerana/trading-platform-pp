#!/bin/sh

# Windows
if [[ ("$OSTYPE" == "cygwin") ||  ("$OSTYPE" == "msys")]]; then 
    ./build/release/trading-platform-pp
# Linux
else
    ./build/trading-platform-pp 
fi