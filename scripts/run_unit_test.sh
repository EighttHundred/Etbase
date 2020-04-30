#!/bin/bash
for file in `ls ../Etbase/unit_test`;do \
    ../Etbase/unit_test/$file; \
    if [ ! $? -eq 0 ];then
        echo "found error in test $file";
    else 
        echo "test $file success";
    fi
done