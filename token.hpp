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

// Delimiters
const std::string COMMA = ",";
const std::string SEMICOLON = ";";

const std::string LPAREN = "(";
const std::string RPAREN = ")";
const std::string LBRACE = "{";
const std::string RBRACE = "}";

// Keywords
const std::string FUNCTION = "fn";
const std::string LET = "let";

const std::unordered_map<std::string, std::string> keywords = {
	{"fn", FUNCTION}, {"let", LET}
};
} // namespace Tok
