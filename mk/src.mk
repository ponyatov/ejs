C += $(wildcard src/*.c*)
H += $(wildcard inc/*.h*)
C += $(wildcard hw/$(HW)/src/*.c*)
H += $(wildcard hw/$(HW)/inc/*.h*)
C += $(wildcard os/$(OS)/src/*.c*)
H += $(wildcard os/$(OS)/inc/*.h*)
J += $(wildcard lib/.boot*) $(wildcard lib/*.js)

CP += $(TMP)/js.parser.cpp $(TMP)/js.lexer.cpp
HP += $(TMP)/js.parser.hpp
