AR=ar	
AR_FLAG=-crv
LIB_FILE=$(LIB_DIR)/libEtbase.a
SRC_FILE=$(wildcard *.cpp)
OBJ_DIR:=$(PRO)/obj
Etbase:gen_obj
	$(AR) $(AR_FLAG) $(LIB_FILE) $(wildcard $(OBJ_DIR)/*.o)
gen_obj:
	for file in $(SRC_FILE);do \
		$(CC) $(CC_FLAG) -c \
		-o $(OBJ_DIR)/`echo $$file|sed 's/.cpp/.o/g'` \
		$$file; \
	done