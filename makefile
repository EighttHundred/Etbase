#!/bin/bash
.PHONY:Etbase genlib test
export INC_DIR=$(PWD)/include
export SRC_DIR=$(PWD)/src
export PRO=$(PWD)/Etbase
export LIB_DIR:=$(PRO)/lib
export CC=c++
export CC_FLAG=-g
Etbase:
	$(MAKE) -C src
test:
	$(MAKE) -C test
genlib:
	sh scripts/gen_lib.sh
