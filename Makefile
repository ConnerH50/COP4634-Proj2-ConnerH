CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -pthread 


OBJECTS = mt-collatz.o 

mt-collatz:  $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) *.o main final mt-collatz


