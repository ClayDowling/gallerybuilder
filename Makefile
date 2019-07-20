PROGNAME=buildgallery
OBJS=$(patsubst %.cpp, %.o, $(wildcard *.cpp))
CXXFLAGS=-std=c++17

$(PROGNAME): $(OBJS)
	$(CXX) -o $@ $^ -lstdc++fs

clean:
	rm -f $(PROGNAME)
	rm -f *.o