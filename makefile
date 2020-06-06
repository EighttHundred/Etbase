#!/bin/bash
.PHONY:Etbase genlib test runtest run
export INC_DIR=$(PWD)/include
export SRC_DIR=$(PWD)/src
export LIB_DIR=$(PWD)/lib
export LIB_FILE=$(LIB_DIR)/libEtbase.a
export CC=c++
export CC_FLAG=-g
export CC_LIB_FLAG=-L $(LIB_DIR) -lEtbase -lpthread
export TOOL_DIR=$(PWD)/scripts
Etbase:
	$(MAKE) -C src
test:Etbase
	$(MAKE) -C test
install:
	bash $(TOOL_DIR)/install.sh
uninstall:
	bash $(TOOL_DIR)/uninstall.sh
configure:
	bash $(TOOL_DIR)/configure.sh
run:run_unit_test

run_unit_test:Etbase
	$(MAKE) -C unit_test
