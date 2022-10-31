#!/bin/env sh

sudo apt update -y
sudo apt install gcc-9 g++-9 ninja-build cmake -y
mkdir build && cd build
cmake .. && make
./tests/lexer_test
./tests/parser_test
./tests/ast_test
