CXX=g++
CFLAGS= -c -g -O3 -Wall -Wextra -Weffc++ -pedantic -pg
LDFLAGS=

SOURCES=octree.cpp octreetest.cpp vec3d.cpp
OBJECTS=$(SOURCES:.cpp=.o)

EXE=main

all: makefile $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
		$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXE)
