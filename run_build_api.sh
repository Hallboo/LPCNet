#!/bin/bash

# rebuild api and reinstall
# LPCNet must install in /usr/lib
# 1. make && make install
# 2. ln -s  /usr/local/lib/liblpcnet.so.0.0.0 /usr/lib/liblpcnet.so.0
# finally in /usr/lib:
#   liblpcnet.so.0 -> /usr/local/lib/liblpcnet.so.0.0.0

# python
rm /home/herb/anaconda3/lib/python3.8/site-packages/lpcnet*
rm -rf build

python setup.py install

rm -rf build
