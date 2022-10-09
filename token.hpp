#pragma once
#include <string>
#include <unordered_map>

namespace Tok {
const std::string ILLEGAL = "ILLEGAL";
const std::string EOF_MARK = "";

// Identifiers and literals
const std::string IDENT = "IDENT";
const std::string INT = "INT";

// Operators
const std::string ASSIGN = "=";
const std::string PLUS = "+";
const std::string MINUS = "-";
const std::string BANG = "!";
const std::string ASTERISK = "*";
const std::string SLASH = "/";
const std::string LT = "<";
const std::string GT = ">";
const std::string EQ = "==";
const std::string NOT_EQ = "!=";

// Delimiters
const std::string COMMA = ",";
const std::string SEMICOLON = ";";

const std::string LPAREN = "(";
const std::string RPAREN = ")";
const std::string LBRACE = "{";
const std::string RBRACE = "}";

// Keywords
const std::string FUNCTION = "FUNCTION";
const std::string LET = "LET";
const std::string IF = "IF";
const std::string ELSE = "ELSE";
const std::string RETURN = "RETURN";
const std::string TRUE = "TRUE";
const std::string FALSE = "FALSE";

const std::unordered_map<std::string, std::string> keywords = {
    {"fn", FUNCTION}, {"let", LET},   {"true", TRUE},	 {"false", FALSE},
    {"if", IF},	      {"else", ELSE}, {"return", RETURN}};

enum class EnumToken {
	ILLEGAL,
	EOF_MARK,

	IDENT,
	INT,

	ASSIGN,
	PLUS,
	MINUS,
	BANG,
	ASTERISK,
	SLASH,
	LT,
	GT,
	EQ,
	NOT_EQ,

	COMMA,
	SEMICOLON,

	LPAREN,
	RPAREN,
	LBRACE,
	RBRACE,

	FUNCTION,
	LET,
	IF,
	ELSE,
	RETURN,
	TRUE,
	FALSE
};

const std::unordered_map<EnumToken, std::string> EnumToString = {
    {EnumToken::ILLEGAL, ILLEGAL},
    {EnumToken::EOF_MARK, EOF_MARK},

    {EnumToken::IDENT, IDENT},
    {EnumToken::INT, INT},

    {EnumToken::ASSIGN, ASSIGN},
    {EnumToken::PLUS, PLUS},
    {EnumToken::MINUS, MINUS},
    {EnumToken::BANG, BANG},
    {EnumToken::ASTERISK, ASTERISK},
    {EnumToken::SLASH, SLASH},
    {EnumToken::LT, LT},
    {EnumToken::GT, GT},
    {EnumToken::EQ, EQ},
    {EnumToken::NOT_EQ, NOT_EQ},

    {EnumToken::COMMA, COMMA},
    {EnumToken::SEMICOLON, SEMICOLON},

    {EnumToken::LPAREN, LPAREN},
    {EnumToken::RPAREN, RPAREN},
    {EnumToken::LBRACE, LBRACE},
    {EnumToken::RBRACE, RBRACE},

    {EnumToken::FUNCTION, FUNCTION},
    {EnumToken::LET, LET},
    {EnumToken::IF, IF},
    {EnumToken::ELSE, ELSE},
    {EnumToken::RETURN, RETURN},
    {EnumToken::TRUE, TRUE},
    {EnumToken::FALSE, FALSE}};

const std::unordered_map<std::string, EnumToken> StringToEnum = {
    {ILLEGAL, EnumToken::ILLEGAL},
    {EOF_MARK, EnumToken::EOF_MARK},

    {IDENT, EnumToken::IDENT},
    {INT, EnumToken::INT},

    {ASSIGN, EnumToken::ASSIGN},
    {PLUS, EnumToken::PLUS},
    {MINUS, EnumToken::MINUS},
    {BANG, EnumToken::BANG},
    {ASTERISK, EnumToken::ASTERISK},
    {SLASH, EnumToken::SLASH},
    {LT, EnumToken::LT},
    {GT, EnumToken::GT},
    {EQ, EnumToken::EQ},
    {NOT_EQ, EnumToken::NOT_EQ},

    {COMMA, EnumToken::COMMA},
    {SEMICOLON, EnumToken::SEMICOLON},

    {LPAREN, EnumToken::LPAREN},
    {RPAREN, EnumToken::RPAREN},
    {LBRACE, EnumToken::LBRACE},
    {RBRACE, EnumToken::RBRACE},

    {FUNCTION, EnumToken::FUNCTION},
    {LET, EnumToken::LET},
    {IF, EnumToken::IF},
    {ELSE, EnumToken::ELSE},
    {RETURN, EnumToken::RETURN},
    {TRUE, EnumToken::TRUE},
    {FALSE, EnumToken::FALSE}};
} // namespace Tok
