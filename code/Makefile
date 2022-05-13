EXENAME = main
OBJS = main.o Graph.o Test.o parseGraph.o user.o

CXX = clang++
CXXFLAGS = -std=c++0x -c -g -O0 -Wall -Wextra
LD = clang++
LDFLAGS = -std=c++0x

all: ${EXENAME}

$(EXENAME): $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

main.o: main.cpp
	$(CXX) $< $(CXXFLAGS)

user.o: user.cpp
	$(CXX) $< $(CXXFLAGS)

Graph.o: Graph.cpp
	$(CXX) $< $(CXXFLAGS)

Test.o: Test.cpp
	$(CXX) $< $(CXXFLAGS)

parseGraph.o: parseGraph.cpp
	$(CXX) $< $(CXXFLAGS)

clean:
	-rm -f *.o $(EXENAME)