
SOURCES     = tween_demo.cpp
LIB         = betweener
LIBPATH     = ../src
INCLUDEDIRS = -I$(LIBPATH)
LIBDIRS     = -L$(LIBPATH) -l$(LIB)
OBJECTS     = $(SOURCES:.cpp=.o)
BINS        = $(SOURCES:.cpp=)
DEBUG       = -g
CXXFLAGS    = -Wall -Werror -ansi  -Wno-write-strings $(DEBUG) $(INCLUDEDIRS)
LDFLAGS     = -Wall -Werror -Wl,-rpath,'$$ORIGIN/$(LIBPATH)' -stdlib $(DEBUG) $(LIBDIRS)
CXX         = g++
CLANG       = clang

all: $(BINS)

run: all
	./$(BINS)

valgrind: all    
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=25 --track-fds=yes ./$(BINS)

$(OBJECTS): $(SOURCES)
	$(CXX) $(CXXFLAGS) -c $<

$(BINS): $(OBJECTS)
	$(CXX) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(BINS) $(OBJECTS)

analyze: all
	$(CLANG) $(INCLUDEDIRS) --analyze *.cpp

# LD_LIBRARY_PATH=../src 
