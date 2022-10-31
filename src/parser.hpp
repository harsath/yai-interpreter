#pragma once
#include "ast.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include <functional>

namespace Parser {
using PrefixParseFunctionType = std::function<Ast::Expression()>;
using InfixParseFunctionType = std::function<Ast::Expression(Ast::Expression)>;
class Parser {
      public:
	std::shared_ptr<Lex::Lexer> l;
	Lex::Token curToken;
	Lex::Token peekToken;
	std::vector<std::string> errorList;
	std::unordered_map<Lex::TokenType, PrefixParseFunctionType>
	    prefixParseFunctions;
	std::unordered_map<Lex::TokenType, InfixParseFunctionType>
	    infixParseFunctions;

	Parser(std::shared_ptr<Lex::Lexer> l);
	std::shared_ptr<Ast::Program> parseProgram();
	const std::vector<std::string> &errors();
	void registerPrefix(Lex::TokenType, PrefixParseFunctionType);
	void registerInfix(Lex::TokenType, InfixParseFunctionType);

      private:
	void nextToken();
	std::shared_ptr<Ast::Statement> parseStatement();
	std::shared_ptr<Ast::LetStatement> parseLetStatement();
	std::shared_ptr<Ast::ReturnStatement> parseReturnStatement();
	bool curTokenIs(Lex::TokenType);
	bool peekTokenIs(Lex::TokenType);
	bool expectedPeek(Lex::TokenType);
	void peekError(Lex::TokenType);
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
const std::vector<std::string> &Parser::errors() { return this->errorList; }
void Parser::peekError(Lex::TokenType type) {
	std::string message = "expected next token to be " + type +
			      ", but got " + this->peekToken.type + " instead";
	this->errorList.emplace_back(std::move(message));
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
	case Tok::EnumToken::RETURN:
		return this->parseReturnStatement();
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
	while (!this->curTokenIs(Tok::SEMICOLON)) { this->nextToken(); }

	return let_stmt;
}
std::shared_ptr<Ast::ReturnStatement> Parser::parseReturnStatement() {
	std::shared_ptr<Ast::ReturnStatement> return_stmt =
	    std::make_shared<Ast::ReturnStatement>();
	return_stmt->token = this->curToken;
	this->nextToken();

	// TODO: We're skipping the expression until semicolon
	while (!this->curTokenIs(Tok::SEMICOLON)) { this->nextToken(); }
	return return_stmt;
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
		this->peekError(type);
		return false;
	}
}
void Parser::registerPrefix(Lex::TokenType token_type,
			    PrefixParseFunctionType fn) {
	this->prefixParseFunctions[token_type] = fn;
}
void Parser::registerInfix(Lex::TokenType token_type,
			   InfixParseFunctionType fn) {
	this->infixParseFunctions[token_type] = fn;
}
} // namespace Parser
