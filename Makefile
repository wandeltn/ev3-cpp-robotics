filename := main
appname := bin/$(filename)

CXX_EV3 := arm-linux-gnueabi-g++
CXX_WIN := g++
CXXFLAGS := -std=c++17 -Wall -pthread -Wno-psabi -MD

export EV3_MODE = 1

CXX := 
ifdef EV3_MODE
CXX := $(CXX_EV3)
else
CXX := $(CXX_WIN)
endif

srcfiles := $(shell find . -type f -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))
dependencies := $(patsubst %.cpp, %.d, $(srcfiles))

LAST_PUSH_HTML = .last_push_html
LAST_PUSH = .last_push

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(objects)
	rm -f $(shell find . -type f -name "*.d")
	rm -f $(LAST_PUSH)
	rm -f $(LAST_PUSH_HTML)

dist-clean: clean
	rm -f *~ .depend


FILES_HTML = $(shell find . -name *.html)
SCP = robot@ev3dev.local:
# SCP = robot@192.168.178.74:
SCP_HTML = $(SCP)public/

.PHONY : html
html : $(LAST_PUSH_HTML)

$(LAST_PUSH_HTML) : $(FILES_HTML)
	scp $? $(SCP_HTML)
	touch $(LAST_PUSH_HTML)


FILES = $(appname)


.PHONY : push
push : $(LAST_PUSH)

$(LAST_PUSH):
	sudo docker run --rm -it --mount type=bind,source="$(shell pwd)",target=/home/compiler ev3cc make
	scp $(appname) $(SCP)
	touch $(LAST_PUSH)

include .depend