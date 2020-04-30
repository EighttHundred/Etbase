LIB_OPTION=-L $(LIB_DIR) -lEtbase -lpthread
TEST_DIR=$(PRO)/test
test:
	for file in $(wildcard *.cpp);do \
		$(CC) $(CC_FLAG) \
		-o $(TEST_DIR)/`echo $$file|sed 's/.cpp//g'` \
		$$file $(LIB_OPTION); \
	done