#pragma once
#include "token.hpp"
#include <iostream>
#include <string>

namespace Lex {
using TokenType = std::string;

bool isLetter(char);
bool isDigit(char);
std::string lookup_ident(const std::string &);

class Token {
      public:
	TokenType type;
	std::string literal;
	Token(TokenType input_type, std::string input_literal);
	Token(const Token &input_token);
	Token &operator=(const Token &input_token);
	Token();
	friend std::ostream &operator<<(std::ostream &os, const Token &token);
};

Token::Token(TokenType input_type, std::string input_literal)
    : type{std::move(input_type)}, literal{std::move(input_literal)} {}

Token::Token(const Token &input_token)
    : type{input_token.type}, literal{input_token.literal} {}

Token::Token() {}

Token &Token::operator=(const Token &input_token) {
	this->type = input_token.type;
	this->literal = input_token.literal;
	return *this;
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
	os << "{Type:" << token.type << " Literal:" << token.literal << "}";
	return os;
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

      private:
	std::string readIdentifier();
	std::string readNumber();
	void skipWhitespace();
	char peekChar();
};

Lexer::Lexer(std::string input_string)
    : input{std::move(input_string)}, readPosition{0} {
	this->readChar();
}
void Lexer::readChar() {
	if (this->readPosition >= this->input.length()) {
		this->ch = 0;
	} else {
		this->ch = this->input[this->readPosition];
	}
	this->position = this->readPosition;
	this->readPosition++;
}

char Lexer::peekChar() {
	if (this->readPosition >= this->input.length()) {
		return 0;
	} else {
		return this->input[this->readPosition];
	}
}

Token Lexer::nextToken() {
	Token tok;
	this->skipWhitespace();
	switch (this->ch) {
	case '=':
		if (this->peekChar() == '=') {
			tok = Token{Tok::EQ, "=="};
			this->readChar();
		} else {
			tok = Token{Tok::ASSIGN, std::string{this->ch}};
		}
		this->readChar();
		break;
	case ';':
		tok = Token{Tok::SEMICOLON, std::string{this->ch}};
		this->readChar();
		break;
	case '(':
		tok = Token{Tok::LPAREN, std::string{this->ch}};
		this->readChar();
		break;
	case ')':
		tok = Token{Tok::RPAREN, std::string{this->ch}};
		this->readChar();
		break;
	case ',':
		tok = Token{Tok::COMMA, std::string{this->ch}};
		this->readChar();
		break;
	case '+':
		tok = Token{Tok::PLUS, std::string{this->ch}};
		this->readChar();
		break;
	case '-':
		tok = Token{Tok::MINUS, std::string{this->ch}};
		this->readChar();
		break;
	case '!':
		if (this->peekChar() == '=') {
			tok = Token{Tok::NOT_EQ, "!="};
			this->readChar();
		} else {
			tok = Token{Tok::BANG, std::string{this->ch}};
		}
		this->readChar();
		break;
	case '*':
		tok = Token{Tok::ASTERISK, std::string{this->ch}};
		this->readChar();
		break;
	case '/':
		tok = Token{Tok::SLASH, std::string{this->ch}};
		this->readChar();
		break;
	case '<':
		tok = Token{Tok::LT, std::string{this->ch}};
		this->readChar();
		break;
	case '>':
		tok = Token{Tok::GT, std::string{this->ch}};
		this->readChar();
		break;
	case '{':
		tok = Token{Tok::LBRACE, std::string{this->ch}};
		this->readChar();
		break;
	case '}':
		tok = Token{Tok::RBRACE, std::string{this->ch}};
		this->readChar();
		break;
	case 0:
		tok = Token{Tok::EOF_MARK, ""};
		this->readChar();
		break;
	default:
		if (isLetter(this->ch)) {
			std::string literal = this->readIdentifier();
			std::string type = lookup_ident(literal);
			tok = Token{type, literal};
		} else if (isDigit(this->ch)) {
			std::string literal = this->readNumber();
			std::string type = Tok::INT;
			tok = Token{type, literal};
		} else {
			tok = Token{Tok::ILLEGAL, "ILLEGAL"};
		}
	}
	return tok;
}

std::string Lexer::readIdentifier() {
	std::string returner{""};
	while (isLetter(this->ch)) {
		returner += this->ch;
		this->readChar();
	}
	return returner;
}

std::string Lexer::readNumber() {
	std::string returner = "";
	while (isDigit(this->ch)) {
		returner += this->ch;
		this->readChar();
	}
	return returner;
}

void Lexer::skipWhitespace() {
	while ((this->ch == ' ') || (this->ch == '\t') || (this->ch == '\n') ||
	       (this->ch == '\r')) {
		this->readChar();
	}
}

bool isLetter(char x) {
	return (('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z') || (x == '_'));
}

bool isDigit(char x) { return (('0' <= x) && ('9' >= x)); }

std::string lookup_ident(const std::string &ident) {
	if (Tok::keywords.find(ident) == Tok::keywords.end()) {
		return Tok::IDENT;
	}
	return Tok::keywords.at(ident);
}

} // namespace Lex
