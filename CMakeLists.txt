cmake_minimum_required(VERSION 3.10)
project(
	yai_interpreter
	VERSION "0.1.0"
	DESCRIPTION "Yai Interpreter"
	)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(tests)
add_subdirectory(src)
