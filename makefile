CXX=g++
CFLAGS= -c -O2 -Wall -Wextra -Weffc++ -pedantic
LDFLAGS=

SOURCES=octree.cpp octreetest.cpp
OBJECTS=$(SOURCES:.cpp=.o)

EXE=main

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
		$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXE)
