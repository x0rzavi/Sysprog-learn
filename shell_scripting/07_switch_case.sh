#!/usr/bin/env bash

read -p "Enter name: " name

case $name in
"Alex" | "alex")
  echo -e "Hi A"
  ;;
"Bob" | "bob")
  echo -e "Hi B"
  ;;
*)
  echo -e "Hello stranger"
  ;;
esac
