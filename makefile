#!/bin/bash
.PHONY:Etbase genlib test runtest run
export INC_DIR=$(PWD)/include
export SRC_DIR=$(PWD)/src
export PRO=$(PWD)/Etbase
export LIB_DIR:=$(PRO)/lib
export CC=c++
export CC_FLAG=-g
export CC_LIB_FLAG=-L $(LIB_DIR) -lEtbase -lpthread
export TOOL_DIR=$(PWD)/scripts
Etbase:
	$(MAKE) -C src
test:
	$(MAKE) -C test
genlib:
	sh $(TOOL_DIR)/gen_lib.sh
run:run_unit_test

run_unit_test:Etbase
	$(MAKE) -C unit_test
