#include "lexer.hpp"
#include "test_helper.hpp"
#include <vector>

int main(int argc, const char *argv[]) {
	std::string input = "=+(){},;";
	std::vector<Token> tests = {
	    Token{ASSIGN, "="}, Token{PLUS, "+"},      Token{LPAREN, "("},
	    Token{RPAREN, ")"}, Token{LBRACE, "{"},    Token{RBRACE, "}"},
	    Token{COMMA, ","},	Token{SEMICOLON, ";"}, Token{EOF_MARK, ""}};
	Lexer lexer = Lexer(input);
	for (const Token &token : tests) {
		Token current_token = lexer.nextToken();
		ASSERT_EQ(token.literal, current_token.literal,
			  std::string{std::string{"Test literal: "} +
				      std::string{token.literal}});
	}

	return 0;
}
