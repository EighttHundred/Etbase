#!/bin/bash
LIB_DIR=/usr/lib/x86_64-linux-gnu/Etbase
LIB_FILE=$LIB_DIR/libEtbase.a
INC_DIR=/usr/include/Etbase

if [ ! -d $LIB_DIR ];then
    sudo mkdir -p $LIB_DIR
fi
if [ -e $LIB_FILE ];then
    sudo rm $LIB_FILE
fi
sudo cp lib/libEtbase.a $LIB_FILE
if [ -d $INC_DIR ];then
    sudo rm -r $INC_DIR
fi
sudo cp -r include $INC_DIR
echo install success
