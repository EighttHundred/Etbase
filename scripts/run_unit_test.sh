#!/bin/bash
echo -e "\nstart unit test\n"
for file in $(ls ../unit_test | grep -E ".bin$");do 
    echo "**test $file";
    ../unit_test/$file;
    if [ ! $? -eq 0 ];then
        echo "**failed";
    else 
        echo "**success";
    fi
    echo 
done