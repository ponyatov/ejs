bin/$(MODULE): $(C) $(CP) $(H) $(HP)
	$(CXX) $(CFLAGS) -o $@ $(C) $(CP) $(L)
# cmake -S $(CWD) -B $(TMP)/$(MODULE)
# cmake --build      $(TMP)/$(MODULE)
# cmake --install    $(TMP)/$(MODULE)

$(TMP)/%.lexer.cpp: $(SRC)/%.lex
	flex -o $@ $<
$(TMP)/%.parser.cpp: $(SRC)/%.yacc
	bison -o $@ $<
