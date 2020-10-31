#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#

#CXX = g++
#CXX = clang++

EXE = Core
JSON_DIR = ../../extlibs/json 
INDICATORS_DIR = ../../extlibs/indicators
SOURCES = main.cpp
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

CXXFLAGS += -I${JSON_DIR}
CXXFLAGS += -I${INDICATORS_DIR}
CXXFLAGS += -std=c++17 -g -Wall -Wformat

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

%.o:src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)
	rm -f $(OBJS)
	./$(EXE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm -f $(EXE) $(OBJS)
