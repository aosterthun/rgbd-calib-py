#!/bin/bash

# third party libs
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/boost/boost_1_55_0/lib:/opt/zmq/current/lib
export PYTHONPATH=$PYTHONPATH:../lib

python3 ./main.py
