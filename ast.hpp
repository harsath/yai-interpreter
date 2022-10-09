#pragma once
#include "lexer.hpp"
#include "token.hpp"
#include <string>
#include <vector>
#include <memory>

namespace Ast {
class Node {
      public:
	virtual std::string tokenLiteral() = 0;
};

class Statement : public Node {
      public:
	virtual void statementNode() = 0;
};

class Expression : public Node {
      public:
	virtual void expressionNode(){}
	virtual std::string tokenLiteral() override { return ""; }
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
};

class Identifier : public Expression {
      public:
	Lex::Token token;
	void expressionNode() override {}
	std::string tokenLiteral() override { return this->token.literal; }
};

class LetStatement : public Statement {
      public:
	Lex::Token token; // LET token
	std::shared_ptr<Identifier> name;
	std::shared_ptr<Expression> value;
	void statementNode() override {}
	std::string tokenLiteral() override {
		return this->token.literal; 
	}
};
} // namespace Ast
