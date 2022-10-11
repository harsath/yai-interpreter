#pragma once
#include "lexer.hpp"
#include "token.hpp"
#include <memory>
#include <string>
#include <vector>

namespace Ast {
class Node {
      public:
	virtual std::string tokenLiteral() = 0;
	virtual std::string string() = 0;
};

class Statement : public Node {
      public:
	virtual void statementNode() = 0;
};

class Expression : public Node {
      public:
	virtual void expressionNode() = 0;
};

// This node is going to be root node of every AST our parser produces
class Program : public Node {
      public:
	std::vector<std::shared_ptr<Statement>> statements;
	std::string tokenLiteral() override {
		if (this->statements.size() > 0) {
			return this->statements.at(0)->tokenLiteral();
		} else {
			return "";
		}
	}
	std::string string() override {
		std::string returner;
		for (std::shared_ptr<Statement> statement : this->statements) {
			returner += statement->string();
		}
		return returner;
	}
};

class Identifier : public Expression {
      public:
	Lex::Token token;
	void expressionNode() override {}
	std::string tokenLiteral() override { return this->token.literal; }
	std::string string() override { return this->token.literal; }
};

class LetStatement : public Statement {
	// let IDENTIFIER = EXPRESSION;
      public:
	Lex::Token token; // LET token
	std::shared_ptr<Identifier> name;
	std::shared_ptr<Expression> value;
	void statementNode() override {}
	std::string tokenLiteral() override { return this->token.literal; }
	std::string string() override {
		std::string returner;
		returner += this->token.literal + " ";
		returner += this->name->string() + " = ";
		if (this->value != nullptr) { this->value->string(); }
		returner += ";";
		return returner;
	}
};

class ReturnStatement : public Statement {
	// return EXPRESSION;
      public:
	Lex::Token token; // RETURN token
	std::shared_ptr<Expression> return_value;
	void statementNode() override {}
	std::string tokenLiteral() override { return this->token.literal; }
	std::string string() override {
		std::string returner;
		returner += this->token.literal + " ";
		if (this->return_value != nullptr) {
			returner += return_value->string();
		}
		return returner;
	}
};

class ExpressionStatement : public Statement {
	// EXPRESSION
      public:
	Lex::Token token;
	std::shared_ptr<Expression> expression;
	void statementNode() override {}
	std::string tokenLiteral() override { return this->token.literal; }
	std::string string() override {
		std::string returner;
		if (this->expression != nullptr) {
			returner += this->expression->string();
		}
	}
};
} // namespace Ast
