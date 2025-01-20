#!/usr/bin/env bash

read -p "Enter name: " name

case $name in
"Avishek" | "avishek") echo -e "Hi Avi" ;;
"Shruti" | "shruti") echo -e "Hi Shru" ;;
esac

echo "THE LENGTH OF THE STRING: ${#name}" #to find the length of the string use "#"

