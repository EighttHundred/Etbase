AR=ar	
AR_FLAG=-crv
LIB_FILE=$(LIB_DIR)/libEtbase.a
SRC_FILE=$(wildcard *.cpp)
OBJ_DIR:=$(PRO)/obj
OBJ_FILE:=$(subst .cpp,.o,$(SRC_FILE))
Etbase:$(LIB_FILE)
$(LIB_FILE):$(OBJ_FILE)
	$(AR) $(AR_FLAG) $(LIB_FILE) $^
.cpp.o:
	$(CC) $(CC_FLAG) -c -o $@ $<