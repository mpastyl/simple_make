CXX = g++
CXXFLAGS = -O2 -Wall -std=c++11
DEPS = simple_make.h

all: simple_make

%.o: %.cpp $(DEPS)
	$(CXX) -c  $(CXXFLAGS) -o $@ $<

.PHONY: clean

simple_make: simple_make.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean: 
	rm -rf *.o simple_make