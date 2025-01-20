#!/usr/bin/env bash

# METHOD-1
for i in {1..10..2}; do #..2 will increment it by 2
  echo "Output: $i"
done

# METHOD-2

read -p "ENTER THE MAXIMUM LIMIT: " max

for i in $( #format <start> <increment> <last>
  seq 2 3 "$max"
); do
  echo "$i"
done
