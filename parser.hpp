#pragma once
#include "ast.hpp"
#include "lexer.hpp"
#include "token.hpp"

namespace Parser {
class Parser {
      public:
	std::shared_ptr<Lex::Lexer> l;
	Lex::Token curToken;
	Lex::Token peekToken;
	Parser(std::shared_ptr<Lex::Lexer> l);
	void nextToken();
	std::shared_ptr<Ast::Program> parseProgram();
	std::shared_ptr<Ast::Statement> parseStatement();
	std::shared_ptr<Ast::LetStatement> parseLetStatement();
	bool curTokenIs(Lex::TokenType);
	bool peekTokenIs(Lex::TokenType);
	bool expectedPeek(Lex::TokenType);
};
Parser::Parser(std::shared_ptr<Lex::Lexer> l) {
	this->l = l;
	// Reading token two times so that `curToken` and `peekToken` are both
	// set.
	this->nextToken();
	this->nextToken();
}
void Parser::nextToken() {
	this->curToken = this->peekToken;
	this->peekToken = this->l->nextToken();
}
std::shared_ptr<Ast::Program> Parser::parseProgram() {
	std::shared_ptr<Ast::Program> program =
	    std::make_shared<Ast::Program>();
	while (this->curToken.type != Tok::EOF_MARK) {
		std::shared_ptr<Ast::Statement> stmt = this->parseStatement();
		if (stmt != nullptr) { program->statements.push_back(stmt); }
		this->nextToken();
	}
	return program;
}
std::shared_ptr<Ast::Statement> Parser::parseStatement() {
	switch (Tok::StringToEnum.at(this->curToken.type)) {
	case Tok::EnumToken::LET:
		return this->parseLetStatement();
	default:
		return nullptr;
	}
}
std::shared_ptr<Ast::LetStatement> Parser::parseLetStatement() {
	// let IDENT = EXPRESSION;
	std::shared_ptr<Ast::LetStatement> let_stmt =
	    std::make_shared<Ast::LetStatement>();
	let_stmt->token = this->curToken;

	if (!this->expectedPeek(Tok::IDENT)) { return nullptr; }

	let_stmt->name = std::make_shared<Ast::Identifier>();
	let_stmt->name->token = this->curToken;

	// TODO: We're skipping the expression until semicolon
	while (this->curTokenIs(Tok::SEMICOLON)) { this->nextToken(); }

	return let_stmt;
}
bool Parser::curTokenIs(Lex::TokenType type) {
	return (this->curToken.type == type);
}
bool Parser::peekTokenIs(Lex::TokenType type) {
	return (this->peekToken.type == type);
}
bool Parser::expectedPeek(Lex::TokenType type) {
	if (this->peekTokenIs(type)) {
		this->nextToken();
		return true;
	} else {
		return false;
	}
}
} // namespace Parser
