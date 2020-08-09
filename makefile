
CXX := g++
LXX = g++

CXXFLAGS := -g -std=c++11 -Isrc/includes -c -lncurses
LXXFLAGS := -g -lncurses

BUILDDIR := build

SRCS := $(notdir $(shell find -name '*.cpp'))
OBJS := $(patsubst %.cpp, $(BUILDDIR)/%.o, $(SRCS))

scenes: builddir $(OBJS) $(SRCS) 
	$(LXX) $(LXXFLAGS) $(OBJS) -o $(BUILDDIR)/scenes

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
	