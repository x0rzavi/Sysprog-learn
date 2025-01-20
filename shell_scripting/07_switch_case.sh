#!/usr/bin/env bash

read -p "Enter name: " name

case $name in
"Alex" | "alex") echo -e "Hi A" ;;
"Bob" | "bob") echo -e "Hi B" ;;
esac

echo "THE LENGTH OF THE STRING: ${#name}" #to find the length of the string use "#"
