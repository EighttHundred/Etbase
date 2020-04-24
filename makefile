#!/bin/bash
.PHONY:Etbase genlib
INC_DIR=include
SRC_DIR=src
SRC_FILE=$(wildcard $(SRC_DIR)/*.cpp)
OBJ_DIR=Etbase/obj
OBJ_FILE=$(subst .cpp,.o,$(SRC_FILE))
LIB_DIR=Etbase/lib
LIB_FILE=$(LIB_DIR)/libEtbase.a
AR=ar	
AR_FLAG=-crv
CC=c++
CC_FLAG=-I $(INC_DIR) -c
Etbase:mklib
	$(shell mv $(SRC_DIR)/*.o $(OBJ_DIR))
mklib:$(OBJ_FILE)
	$(AR) $(AR_FLAG) $(LIB_FILE) $^
.cpp.o:
	$(CC) $(CC_FLAG) -o $@ $<
genlib:
	sh scripts/gen_lib.sh