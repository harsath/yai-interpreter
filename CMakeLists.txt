cmake_minimum_required(VERSION 3.10)
project(
	go_interpreter
	VERSION "0.1.0"
	DESCRIPTION "Interpreter for cxx"
	)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(lexer_test lexer_test.cpp)
