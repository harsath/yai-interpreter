#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define __FILENAME__                                                           \
	(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

static size_t _total_test_count = 0;
static size_t _fail_count = 0;
static size_t _pass_count = 0;

#define ASSERT_TRUE(expression_result, test_name)                              \
	do {                                                                   \
		if (expression_result) {                                       \
			_pass_count++;                                         \
			_total_test_count++;                                   \
			std::cout << "TEST: " << test_name                     \
				  << ", STATUS: " << GREEN_COLOR << "[ OK ]"   \
				  << RESET_COLOR << ", LINE: " << __LINE__     \
				  << ", FILE: " << __FILENAME__ << std::endl;  \
		} else {                                                       \
			_fail_count++;                                         \
			_total_test_count++;                                   \
			std::cout << "TEST: " << test_name                     \
				  << ", STATUS: " << RED_COLOR << "[ FAILED ]" \
				  << RESET_COLOR << ", LINE: " << __LINE__     \
				  << ", FILE: " << __FILENAME__ << std::endl;  \
			exit(EXIT_FAILURE);                                    \
		}                                                              \
	} while (0)

#define ASSERT_FALSE(expression_result, test_name)                             \
	do {                                                                   \
		if (!expression_result) {                                      \
			_pass_count++;                                         \
			_total_test_count++;                                   \
			std::cout << "TEST: " << test_name                     \
				  << ", STATUS: " << GREEN_COLOR << "[ OK ]"   \
				  << RESET_COLOR << ", LINE: " << __LINE__     \
				  << ", FILE: " << __FILENAME__ << std::endl;  \
		} else {                                                       \
			_fail_count++;                                         \
			_total_test_count++;                                   \
			std::cout << "TEST: " << test_name                     \
				  << ", STATUS: " << RED_COLOR << "[ FAILED ]" \
				  << RESET_COLOR << ", LINE: " << __LINE__     \
				  << ", FILE: " << __FILENAME__ << std::endl;  \
			exit(EXIT_FAILURE);                                    \
		}                                                              \
	} while (0)

#define ASSERT_EQ(value_one, value_two, test_name)                             \
	do {                                                                   \
		if (value_one == value_two) {                                  \
			_pass_count++;                                         \
			_total_test_count++;                                   \
			std::cout << "TEST: " << test_name                     \
				  << ", STATUS: " << GREEN_COLOR << "[ OK ]"   \
				  << RESET_COLOR << ", LINE: " << __LINE__     \
				  << ", FILE: " << __FILENAME__ << std::endl;  \
		} else {                                                       \
			_fail_count++;                                         \
			_total_test_count++;                                   \
			std::cout << "TEST: " << test_name                     \
				  << ", STATUS: " << RED_COLOR << "[ FAILED ]" \
				  << RESET_COLOR << ", LINE: " << __LINE__     \
				  << ", FILE: " << __FILENAME__ << std::endl;  \
			exit(EXIT_FAILURE);                                    \
		}                                                              \
	} while (0)

#define TEST_STATS()                                                           \
	do {                                                                   \
		printf("\nTotal Tests: %lu\nTotal tests passed: "              \
		       "%s%lu%s\nTotal tests failed: %s%lu%s\n",               \
		       _total_test_count, GREEN_COLOR, _pass_count,            \
		       RESET_COLOR, RED_COLOR, _fail_count, RESET_COLOR);      \
	} while (0)
