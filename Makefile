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

$(TARGET): $(OBJECTS) Makefile
	$(CC) -shared $(OBJECTS) $(LIBS) -Wl,-rpath,$(PYLIBPATH) -o $@


src/%.o: src/%.cpp $(HEADERS) Makefile
	$(CC) $(CXXFLAGS) -c $< -o $@ -fPIC


clean:
	rm -rf $(OBJECTS) $(TARGET) src/*~ examples/*~ *~


.PHONY: default clean

