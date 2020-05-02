#!/bin/bash
for file in `ls ../Etbase/unit_test`;do \
    echo "**test $file";
    ../Etbase/unit_test/$file;
    if [ ! $? -eq 0 ];then
        echo "**failed";
    else 
        echo "**success";
    fi
done