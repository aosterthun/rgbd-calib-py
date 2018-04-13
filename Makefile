CC = c++
PYLIBPATH = /usr/lib/x86_64-linux-gnu
PYINCPATH = /usr/include/python3.5
LIBS = -L$(PYLIBPATH) -lpthread -ldl  -lutil -lm  -lpython3.5m -lboost_python-py35 -lboost_serialization -lboost_system -lzmq
CXXFLAGS = -std=c++11 -Isrc -I$(PYINCPATH) -O2


SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp, src/%.o, $(SOURCES))
HEADERS = $(wildcard src/*.hpp)

TARGET = lib/pyrgbdcalib.so

default: $(TARGET)
	@echo built $(TARGET)
	c++ -std=c++11 -c examples/kinect_client.cpp -o examples/kinect_client.o -Isrc
	c++ -std=c++11 examples/kinect_client.o src/play.o src/record.o src/RGBDRIClient.o src/FileBuffer.o src/ChronoMeter.o src/GenericMessage.o -o examples/kinect_client -lboost_system -lboost_serialization -lzmq -pthread

$(TARGET): $(OBJECTS) Makefile
	$(CC) -shared $(OBJECTS) $(LIBS) -Wl,-rpath,$(PYLIBPATH) -o $@


src/%.o: src/%.cpp $(HEADERS) Makefile
	$(CC) $(CXXFLAGS) -c $< -o $@ -fPIC


clean:
	rm -rf $(OBJECTS) $(TARGET) src/*~ examples/*~ *~


.PHONY: default clean
