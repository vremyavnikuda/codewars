#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <number1> <number2>"
    exit 1
fi
num1=$1
num2=$2
if ! [[ "$num1" =~ ^-?[0-9]+$ ]] || ! [[ "$num2" =~ ^-?[0-9]+$ ]]; then
    echo "Error: Both parameters must be integers"
    exit 1
fi
echo "Parameter 1: $num1"
echo "Parameter 2: $num2"
if [ $num1 -gt $num2 ]; then
    echo "Maximum: $num1"
elif [ $num2 -gt $num1 ]; then
    echo "Maximum: $num2"
else
    echo "Both numbers are equal: $num1"
fi