
CXX := g++
LXX = g++

CXXFLAGS := -W -Wall -Os -std=c++11 -c -lncurses
LXXFLAGS := -W -Wall -s -Os

BUILDDIR := build

SRCS := $(notdir $(shell find -name '*.cpp'))
OBJS := $(patsubst %.cpp, $(BUILDDIR)/%.o, $(SRCS))

scenes: builddir $(OBJS) $(SRCS) 
	$(LXX) $(LXXFLAGS) $(OBJS) -o $(BUILDDIR)/scenes -lncurses

$(BUILDDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: builddir
builddir:
	@mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	@rm -f -r build/

install:
	mkdir -p ~/.local/bin
	cp $(BUILDDIR)/scenes ~/.local/bin/scenes
	
