CC = c++
PYLIBPATH = /usr/lib/x86_64-linux-gnu
PYINCPATH = /usr/include/python3.5
BOOSTLIBPATH = /usr/lib/x86_64-linux-gnu
BOOSTINCPATH = /usr/include
ZMQLIBPATH = /usr/lib/x86_64-linux-gnu
ZMQINCPATH = /usr/include
LIBS = -L$(PYLIBPATH) -lpthread -ldl  -lutil -lm  -lpython3.5m -L$(BOOSTLIBPATH) -lboost_python -L$(ZMQLIBPATH) -lzmq
CXXFLAGS = -std=c++11 -Isrc -I$(PYINCPATH) -I$(BOOSTINCPATH) -I$(ZMQINCPATH) -O2

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp, src/%.o, $(SOURCES))
HEADERS = $(wildcard src/*.hpp)

TARGET = lib/pykinecting.so

default: $(TARGET)
	@echo SOURCES: $(SOURCES)
	@echo built $(TARGET)
	c++ -std=c++11 -c examples/kinect_client.cpp -o examples/kinect_client.o -Isrc
	c++ -std=c++11 examples/kinect_client.o src/Event.o src/KinectDaemon.o src/KinectDaemonHandshake.o src/Observable.o src/PlayCommand.o src/Threadable.o src/ZMQMessageType.o src/ThreadEvent.o src/EventData.o src/GenericMessage.o src/RecordCommand.o -o examples/kinect_client -lboost_system -lboost_serialization -lzmq -pthread

$(TARGET): $(OBJECTS)
	$(CC) -shared $(OBJECTS) $(LIBS) -Wl,-rpath,$(PYLIBPATH) -Wl,-rpath,$(BOOSTLIBPATH) -Wl,-rpath,$(ZMQLIBPATH) -o $@


src/%.o: src/%.cpp $(HEADERS) Makefile
	$(CC) $(CXXFLAGS) -c $< -o $@ -fPIC


clean:
	rm -rf $(OBJECTS) $(TARGET) src/*~ examples/*~ *~


.PHONY: default clean
