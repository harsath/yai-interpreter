#pragma once
#include "token.hpp"
#include <string>

using TokenType = std::string;

class Token {
      public:
	TokenType type;
	std::string literal;
	Token(TokenType input_type, std::string input_literal);
	Token(const Token &input_token);
	Token &operator=(const Token &input_token);
	Token();
};

Token::Token(TokenType input_type, std::string input_literal)
    : type{std::move(input_type)}, literal{std::move(input_literal)} {}

Token::Token(const Token &input_token)
    : type{input_token.type}, literal{input_token.type} {}

Token::Token() {}

Token &Token::operator=(const Token &input_token) {
	this->type = input_token.type;
	this->literal = input_token.literal;
	return *this;
}

class Lexer {
      public:
	std::string input;
	int position;	  // current position in input (points to current char)
	int readPosition; // current reading position in input (after current
			  // char)
	char ch;	  // current char under examination
	Lexer(std::string input_string);
	void readChar();
	Token nextToken();
};

Lexer::Lexer(std::string input_string)
    : input{std::move(input_string)}, readPosition{0} {
	this->readChar();
}
void Lexer::readChar() {
	if (this->readPosition >= input.length()) {
		this->ch = 0;
	} else {
		this->ch = this->input[this->readPosition];
	}
	this->position = this->readPosition;
	this->readPosition++;
}

Token Lexer::nextToken() {
	Token tok;
	switch (this->ch) {
	case '=':
		tok = Token{ASSIGN, std::string{this->ch}};
	case ';':
		tok = Token{SEMICOLON, std::string{this->ch}};
	case '(':
		tok = Token{LPAREN, std::string{this->ch}};
	case ')':
		tok = Token{RPAREN, std::string{this->ch}};
	case ',':
		tok = Token{COMMA, std::string{this->ch}};
	case '+':
		tok = Token{PLUS, std::string{this->ch}};
	case '{':
		tok = Token{LBRACE, std::string{this->ch}};
	case '}':
		tok = Token{RBRACE, std::string{this->ch}};
	case 0:
		tok = Token{"", EOF_MARK};
	}
	this->readChar();
	return tok;
}
