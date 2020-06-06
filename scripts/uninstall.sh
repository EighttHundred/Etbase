#!/bin/bash

LIB_DIR=/usr/lib/x86_64-linux-gnu/Etbase
LIB_FILE=$LIB_DIR/libEtbase.a
INC_DIR=/usr/include/Etbase

if [ -d $LIB_DIR ];then
    sudo rm -r $LIB_DIR
fi
if [ -d $INC_DIR ];then
    sudo rm -r $INC_DIR
fi
echo uninstall success