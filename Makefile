PROGNAME=gallerybuilder
OBJS=$(patsubst %.cpp, %.o, $(wildcard *.cpp))
CXXFLAGS=-std=c++17

$(PROGNAME): $(OBJS)
	$(CXX) -o $@ $^ -lstdc++fs

clean:
	rm -f $(PROGNAME)
	rm -f *.o
	rm -f *.exe

install: $(PROGNAME)
	cp $(PROGNAME).exe ~/bin