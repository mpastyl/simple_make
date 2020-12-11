CXX = g++
CXXFLAGS = -O2 -g -Wall -std=c++11 -pthread
AGS = -O2 -Wall -std=c++11

all: test_main

%.o: %.cpp $(DEPS)§
	$(CXX) -c  $(CXXFLAGS) -o $@ $<

.PHONY: clean



test_main: test_main.o ../Rules.o 
	$(CXX) $(CXXFLAGS) -lgtest -o $@ $^  /usr/local/lib/gtest/libgtest.a /usr/local/lib/gtest/libgtest_main.a
clean:
	rm -rf *.o ../*.o test_main
