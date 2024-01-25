#!/bin/bash

if ls *.o 1> /dev/null 2>&1; then
    rm *.o
    echo "Deleted all *.o files."
else
    echo "No *.o files found."
fi