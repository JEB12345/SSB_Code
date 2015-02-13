#!bin/bash
git pull --recurse-submodules
cd Motor_Driver/
git submodule init
git submodule update
