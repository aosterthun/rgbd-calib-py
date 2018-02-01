CC = c++
PYLIBPATH = /usr/local/Cellar/python3/3.6.4_2/Frameworks/Python.framework/Versions/3.6/lib/
PYINCPATH = /usr/local/Cellar/python3/3.6.4_2/Frameworks/Python.framework/Versions/3.6/include/python3.6m
LIBS = -L$(PYLIBPATH) -lpthread -ldl  -lutil -lm  -lpython3.6m -lboost_python3 -lboost_serialization -lboost_system -lzmq
CXXFLAGS = -std=c++11 -stdlib=libc++ -Isrc -I$(PYINCPATH) -O2


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
