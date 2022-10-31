set(INTERPRETER_LIB_NAME libyai_interpreter)
add_library(
	${INTERPRETER_LIB_NAME}
	./token.hpp
	./lexer.hpp
	./ast.hpp
	./parser.hpp
	)
set_target_properties(
	${INTERPRETER_LIB_NAME}
	PROPERTIES LINKER_LANGUAGE CXX
	)
