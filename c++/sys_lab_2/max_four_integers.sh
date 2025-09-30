#!/bin/bash
if [ $# -ne 4 ]; then
    echo "Usage: $0 <number1> <number2> <number3> <number4>"
    exit 1
fi
num1=$1
num2=$2
num3=$3
num4=$4
if ! [[ "$num1" =~ ^-?[0-9]+$ ]] || ! [[ "$num2" =~ ^-?[0-9]+$ ]] || ! [[ "$num3" =~ ^-?[0-9]+$ ]] || ! [[ "$num4" =~ ^-?[0-9]+$ ]]; then
    echo "Error: All parameters must be integers"
    exit 1
fi
echo "Parameter 1: $num1"
echo "Parameter 2: $num2"
echo "Parameter 3: $num3"
echo "Parameter 4: $num4"
max=$num1
if [ $num2 -gt $max ]; then
    max=$num2
fi
if [ $num3 -gt $max ]; then
    max=$num3
fi
if [ $num4 -gt $max ]; then
    max=$num4
fi
echo "Maximum: $max"