#include <memory>
#include "ast.hpp"
#include "test_helper.hpp"

void test_string();

int main() {
	test_string();

	return 0;
}

void test_string() {
	std::shared_ptr<Ast::Program> program = std::make_shared<Ast::Program>();
	std::shared_ptr<Ast::LetStatement> let_stmt_tmp = std::make_shared<Ast::LetStatement>();
	let_stmt_tmp->token = Lex::Token(Tok::LET, "let");
	std::shared_ptr<Ast::Identifier> identifier_tmp = std::make_shared<Ast::Identifier>();
	identifier_tmp->token = Lex::Token(Tok::IDENT, "my_var");
	let_stmt_tmp->name = identifier_tmp;
	std::shared_ptr<Ast::Identifier> value_tmp = std::make_shared<Ast::Identifier>();
	value_tmp->token = Lex::Token(Tok::IDENT, "another_var");
	let_stmt_tmp->value = value_tmp;
	program->statements.push_back(let_stmt_tmp);
	ASSERT_TRUE(program->statements.at(0)->string() == "let my_var = another_var;", "let statement doesn't match AST generated one");
}
