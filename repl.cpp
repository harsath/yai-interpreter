#include "lexer.hpp"

int main(const int argc, const char *argv[]) {
	while (1) {
		std::cout << ">> ";
		std::string input_string;
		std::getline(std::cin, input_string);
		Lex::Lexer lexer(input_string);
		for (Lex::Token token = lexer.nextToken();
		     token.type != Tok::EOF_MARK; token = lexer.nextToken()) {
			std::cout << token << std::endl;
		}
	}
	return 0;
}
