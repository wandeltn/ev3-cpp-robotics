appname := bin/main

CXX := arm-linux-gnueabi-g++
CXXFLAGS := -std=c++17 -Wno-psabi -MD

srcfiles := $(shell find . -type f -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))
dependencies := $(patsubst %.cpp, %.d, $(srcfiles))

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(objects)
	rm -f $(dependencies)

dist-clean: clean
	rm -f *~ .depend

include .depend