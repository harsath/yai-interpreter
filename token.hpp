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
} // namespace Tok
