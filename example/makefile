SRC_FILE=$(wildcard *.cpp)
BIN_FILE:=$(subst .cpp,.bin,$(SRC_FILE))

test:$(BIN_FILE)
%.bin:%.cpp $(LIB_FILE)
	$(CC) $(CC_FLAG) -o $@ $< $(CC_LIB_FLAG)
	chmod +x $<
clean:
	rm *.bin