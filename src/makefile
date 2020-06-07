AR=ar	
AR_FLAG=-crv
SRC_FILE=$(wildcard *.cpp)
OBJ_FILE:=$(subst .cpp,.o,$(SRC_FILE))
Etbase:$(LIB_FILE)
$(LIB_FILE):$(OBJ_FILE)
	$(AR) $(AR_FLAG) $(LIB_FILE) $^
.cpp.o:
	$(CC) $(CC_FLAG) -c -o $@ $<
clean:
	rm *.o