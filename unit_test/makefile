SRC_FILE=$(wildcard *.cpp)
BIN_FILE:=$(subst .cpp,.bin,$(SRC_FILE))

unit_test:$(BIN_FILE) 
	bash $(TOOL_DIR)/run_unit_test.sh
%.bin:%.cpp $(LIB_FILE)
	$(CC) $(CC_FLAG) -o $@ $< $(CC_LIB_FLAG)
	chmod +x $@
clean:
	rm *.bin
