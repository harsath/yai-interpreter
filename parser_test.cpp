#include "ast.hpp"
#include "parser.hpp"
#include "test_helper.hpp"
#include <string>
#include <vector>

void test_let_statement();
void _test_let_statement(std::shared_ptr<Ast::Statement>, std::string);
void _check_parser_errors(std::shared_ptr<Parser::Parser>);

int main(int argc, const char *argv[]) {
	test_let_statement();

	return 0;
}

void test_let_statement() {
	using namespace Lex;
	std::string input = R""""(
	let x = 5;
	let y = 10;
	let foobar = 838383;
	)"""";
	std::shared_ptr<Lexer> l = std::make_shared<Lexer>(input);
	std::shared_ptr<Parser::Parser> p = std::make_shared<Parser::Parser>(l);
	std::shared_ptr<Ast::Program> program = p->parseProgram();
	_check_parser_errors(p);
	ASSERT_TRUE(program != nullptr, "parseProgram() returned nullptr");
	ASSERT_TRUE(program->statements.size() == 3,
		    "program.statements does not contain 3 statements.");
	std::vector<std::string> tests = {"x", "y", "foobar"};
	size_t i = 0;
	for (const std::string &test : tests) {
		std::shared_ptr<Ast::Statement> stmt =
		    program->statements.at(i);
		_test_let_statement(stmt, test);
		i++;
	}
}

void _test_let_statement(std::shared_ptr<Ast::Statement> s, std::string name) {
	ASSERT_TRUE(s->tokenLiteral() == "let",
		    "statement.tokenLiteral is not 'let'");
	std::shared_ptr<Ast::LetStatement> let_stmt =
	    std::static_pointer_cast<Ast::LetStatement>(s);
	ASSERT_TRUE(let_stmt->name->tokenLiteral() == name,
		    "let_stmt.name.tokenLiteral() does not match `name`");
}

void _check_parser_errors(std::shared_ptr<Parser::Parser> parser) {
	const std::vector<std::string> &errors = parser->errors();
	if (errors.size() == 0) { return; }
	std::cerr << "parser has " << errors.size() << " errors" << std::endl;
	for (const std::string &error : errors) {
		std::cerr << error << std::endl;
	}
	ASSERT_TRUE(false, "Parser has errors");
}
