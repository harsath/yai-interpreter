#include "lexer.hpp"
#include "test_helper.hpp"
#include <vector>

void test_one();
void test_two();
void test_three();
void test_four();
void test_five();

int main(int argc, const char *argv[]) {
	test_one();
	test_two();
	test_three();
	test_four();
	test_five();

	return 0;
}

void test_one() {
	using namespace Lex;
	std::string input = "=+(){},;";
	std::vector<Token> tests = {
	    Token{Tok::ASSIGN, "="}, Token{Tok::PLUS, "+"},
	    Token{Tok::LPAREN, "("}, Token{Tok::RPAREN, ")"},
	    Token{Tok::LBRACE, "{"}, Token{Tok::RBRACE, "}"},
	    Token{Tok::COMMA, ","},  Token{Tok::SEMICOLON, ";"},
	    Token{Tok::EOF_MARK, ""}};
	Lexer lexer = Lexer(input);
	for (const Token &token : tests) {
		Token current_token = lexer.nextToken();
		ASSERT_EQ(token.literal, current_token.literal,
			  std::string{std::string{"Test 1 literal: "} +
				      std::string{token.literal}});
		ASSERT_EQ(token.type, current_token.type,
			  std::string{std::string{"Test 1 type: "} +
				      std::string{token.type}});
	}
}

void test_two() {
	using namespace Lex;
	std::string input = R""""(
		let five = 5;
		let ten = 10;
		let add = fn(x, y) {
			x + y;
		};
		let result = add(five, ten);
		)"""";
	Lexer lexer(input);
	std::vector<Token> tests = {
	    Token{Tok::LET, "let"},	Token{Tok::IDENT, "five"},
	    Token{Tok::ASSIGN, "="},	Token{Tok::INT, "5"},
	    Token{Tok::SEMICOLON, ";"}, Token{Tok::LET, "let"},
	    Token{Tok::IDENT, "ten"},	Token{Tok::ASSIGN, "="},
	    Token{Tok::INT, "10"},	Token{Tok::SEMICOLON, ";"},
	    Token{Tok::LET, "let"},	Token{Tok::IDENT, "add"},
	    Token{Tok::ASSIGN, "="},	Token{Tok::FUNCTION, "fn"},
	    Token{Tok::LPAREN, "("},	Token{Tok::IDENT, "x"},
	    Token{Tok::COMMA, ","},	Token{Tok::IDENT, "y"},
	    Token{Tok::RPAREN, ")"},	Token{Tok::LBRACE, "{"},
	    Token{Tok::IDENT, "x"},	Token{Tok::PLUS, "+"},
	    Token{Tok::IDENT, "y"},	Token{Tok::SEMICOLON, ";"},
	    Token{Tok::RBRACE, "}"},	Token{Tok::SEMICOLON, ";"},
	    Token{Tok::LET, "let"},	Token{Tok::IDENT, "result"},
	    Token{Tok::ASSIGN, "="},	Token{Tok::IDENT, "add"},
	    Token{Tok::LPAREN, "("},	Token{Tok::IDENT, "five"},
	    Token{Tok::COMMA, ","},	Token{Tok::IDENT, "ten"},
	    Token{Tok::RPAREN, ")"},	Token{Tok::SEMICOLON, ";"},
	    Token{Tok::EOF_MARK, ""}};
	for (const Token &token : tests) {
		Token current_token = lexer.nextToken();
		ASSERT_EQ(token.literal, current_token.literal,
			  std::string{std::string{"Test 2 literal: "} +
				      std::string{token.literal}});
		ASSERT_EQ(token.type, current_token.type,
			  std::string{std::string{"Test 2 type: "} +
				      std::string{token.type}});
	}
}

void test_three() {
	using namespace Lex;
	std::string input = R""""(
	let ten = 10;
	!-/*5;
	5 < 10 > 5;
	)"""";
	std::vector<Token> tests = {
	    Token{Tok::LET, "let"},	Token{Tok::IDENT, "ten"},
	    Token{Tok::ASSIGN, "="},	Token{Tok::INT, "10"},
	    Token{Tok::SEMICOLON, ";"}, Token{Tok::BANG, "!"},
	    Token{Tok::MINUS, "-"},	Token{Tok::SLASH, "/"},
	    Token{Tok::ASTERISK, "*"},	Token{Tok::INT, "5"},
	    Token{Tok::SEMICOLON, ";"}, Token{Tok::INT, "5"},
	    Token{Tok::LT, "<"},	Token{Tok::INT, "10"},
	    Token{Tok::GT, ">"},	Token{Tok::INT, "5"},
	    Token{Tok::SEMICOLON, ";"}, Token{Tok::EOF_MARK, ""}};
	Lexer lexer(input);
	for (const Token &token : tests) {
		Token current_token = lexer.nextToken();
		ASSERT_EQ(token.literal, current_token.literal,
			  std::string{std::string{"Test 3 literal: "} +
				      std::string{token.literal}});
		ASSERT_EQ(token.type, current_token.type,
			  std::string{std::string{"Test 3 type: "} +
				      std::string{token.type}});
	}
}

void test_four() {
	using namespace Lex;
	std::string input = R""""(
	if (5 < 10) {
		return true;
	} else {
		return false;
	}
	)"""";
	std::vector<Token> tests = {
	    Token{Tok::IF, "if"},	Token{Tok::LPAREN, "("},
	    Token{Tok::INT, "5"},	Token{Tok::LT, "<"},
	    Token{Tok::INT, "10"},	Token{Tok::RPAREN, ")"},
	    Token{Tok::LBRACE, "{"},	Token{Tok::RETURN, "return"},
	    Token{Tok::TRUE, "true"},	Token{Tok::SEMICOLON, ";"},
	    Token{Tok::RBRACE, "}"},	Token{Tok::ELSE, "else"},
	    Token{Tok::LBRACE, "{"},	Token{Tok::RETURN, "return"},
	    Token{Tok::FALSE, "false"}, Token{Tok::SEMICOLON, ";"},
	    Token{Tok::RBRACE, "}"},	Token{Tok::EOF_MARK, ""}};
	Lexer lexer(input);
	for (const Token &token : tests) {
		Token current_token = lexer.nextToken();
		ASSERT_EQ(token.literal, current_token.literal,
			  std::string{std::string{"Test 4 literal: "} +
				      std::string{token.literal}});
		ASSERT_EQ(token.type, current_token.type,
			  std::string{std::string{"Test 4 type: "} +
				      std::string{token.type}});
	}
}

void test_five() {
	using namespace Lex;
	std::string input = R""""(
	if (5 == 10) {
		return true;
	} 
	if (5 != 10) {
		return true;
	} 
	)"""";
	std::vector<Token> tests = {
	    Token{Tok::IF, "if"},	  Token{Tok::LPAREN, "("},
	    Token{Tok::INT, "5"},	  Token{Tok::EQ, "=="},
	    Token{Tok::INT, "10"},	  Token{Tok::RPAREN, ")"},
	    Token{Tok::LBRACE, "{"},	  Token{Tok::RETURN, "return"},
	    Token{Tok::TRUE, "true"},	  Token{Tok::SEMICOLON, ";"},
	    Token{Tok::RBRACE, "}"},	  Token{Tok::IF, "if"},
	    Token{Tok::LPAREN, "("},	  Token{Tok::INT, "5"},
	    Token{Tok::NOT_EQ, "!="},	  Token{Tok::INT, "10"},
	    Token{Tok::RPAREN, ")"},	  Token{Tok::LBRACE, "{"},
	    Token{Tok::RETURN, "return"}, Token{Tok::TRUE, "true"},
	    Token{Tok::SEMICOLON, ";"},	  Token{Tok::RBRACE, "}"},
	    Token{Tok::EOF_MARK, ""}};
	Lexer lexer(input);
	for (const Token &token : tests) {
		Token current_token = lexer.nextToken();
		ASSERT_EQ(token.literal, current_token.literal,
			  std::string{std::string{"Test 5 literal: "} +
				      std::string{token.literal}});
		ASSERT_EQ(token.type, current_token.type,
			  std::string{std::string{"Test 5 type: "} +
				      std::string{token.type}});
	}
}
