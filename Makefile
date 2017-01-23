CC = c++
PYLIBPATH = /usr/lib/x86_64-linux-gnu
PYINCPATH = /usr/include/python3.4
BOOSTLIBPATH = /opt/boost/boost_1_62_0/lib
BOOSTINCPATH = /opt/boost/boost_1_62_0/include
ZMQLIBPATH = /opt/zmq/current/lib
ZMQINCPATH = /opt/zmq/current/include
LIBS = -L$(PYLIBPATH) -lpthread -ldl  -lutil -lm  -lpython3.4m -L$(BOOSTLIBPATH) -lboost_python -L$(ZMQLIBPATH) -lzmq
CXXFLAGS = -std=c++11 -Isrc -I$(PYINCPATH) -I$(BOOSTINCPATH) -I$(ZMQINCPATH) -O2 


SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp, src/%.o, $(SOURCES))
HEADERS = $(wildcard src/*.hpp)

TARGET = lib/pyrgbdcalib.so

default: $(TARGET)
	@echo built $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -shared $(OBJECTS) $(LIBS) -Wl,-rpath,$(PYLIBPATH) -Wl,-rpath,$(BOOSTLIBPATH) -Wl,-rpath,$(ZMQLIBPATH) -o $@


src/%.o: src/%.cpp $(HEADERS) Makefile
	$(CC) $(CXXFLAGS) -c $< -o $@ -fPIC


clean:
	rm -rf $(OBJECTS) $(TARGET) src/*~ examples/*~ *~


.PHONY: default clean

