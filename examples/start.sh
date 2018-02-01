# if not, this path will be used
GUACAMOLE=/opt/guacamole/master
AVANGO=/opt/avango/master

# third party libs
export LD_LIBRARY_PATH=/opt/Awesomium/lib:/opt/lamure/install/lib

# schism
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/bernste4/src/schism/lib/linux_x86
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/schism/current/lib/linux_x86

# avango and rgbdpy
export LD_LIBRARY_PATH=$AVANGO/lib:$GUACAMOLE/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH:../lib:$AVANGO/lib/python3.5:$AVANGO/examples

python3.6 ./main.py "$@"
