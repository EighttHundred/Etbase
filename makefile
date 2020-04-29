#!/bin/bash
.PHONY:Etbase genlib test
export INC_DIR=$(PWD)/include
export SRC_DIR=$(PWD)/src
export PRO=$(PWD)/Etbase
SRC_FILE=$(wildcard $(SRC_DIR)/*.cpp)
OBJ_DIR:=$(PRO)/obj
OBJ_FILE=$(subst .cpp,.o,$(SRC_FILE))
export LIB_DIR:=$(PRO)/lib
LIB_FILE=$(LIB_DIR)/libEtbase.a
AR=ar	
AR_FLAG=-crv
export CC=c++
export CC_FLAG=-I $(INC_DIR) -c -g
Etbase:mklib
	$(shell mv $(SRC_DIR)/*.o $(OBJ_DIR))
mklib:$(OBJ_FILE)
	$(AR) $(AR_FLAG) $(LIB_FILE) $^
.cpp.o:
	$(CC) $(CC_FLAG) -o $@ $<
genlib:
	sh scripts/gen_lib.sh
test:
	$(MAKE) -C $(SRC_DIR)/test
