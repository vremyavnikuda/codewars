#!/bin/bash
if [ $# -ne 2 ]; then
    echo "Usage: $0 <string1> <string2>"
    exit 1
fi
string1=$1
string2=$2
echo "Script name: $0"
echo "Parameter 1: $string1"
echo "Parameter 2: $string2"
if [ "$string1" = "$string2" ]; then
    echo "The strings are equal."
else
    echo "The strings are not equal."
fi