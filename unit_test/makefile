UNIT_TEST_DIR=$(PRO)/unit_test
unit_test:gen_unit_test
	sh $(TOOL_DIR)/run_unit_test.sh
gen_unit_test:
	for file in $(wildcard *.cpp);do \
		$(CC) $(CC_FLAG) \
		-o $(UNIT_TEST_DIR)/`echo $$file|sed 's/.cpp//g'` \
		$$file $(CC_LIB_FLAG); \
	done