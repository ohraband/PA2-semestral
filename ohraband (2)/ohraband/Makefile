CXX=g++
CXXFLAGS= -Wall -pedantic -g -std=c++17
LDLIBS= -lstdc++fs -lncurses
OUTFILE= ohraband
SOURCES = $(wildcard src/*.cpp)



all: compile doc

compile: $(SOURCES:.cpp=.o)
	$(CXX) $(CXXFLAGS) $(SOURCES:.cpp=.o) -o $(OUTFILE) $(LDLIBS)

run:
	./$(OUTFILE)

clean:
	$(RM) $(SOURCES:.cpp=.o) $(OUTFILE)
	$(RM) -R doc

doc:
	doxygen Doxyfile