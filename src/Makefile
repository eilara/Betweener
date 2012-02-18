
SOURCES     = Vector.cpp                    \
				easing.cpp                  \
				IProxy.cpp                  \
				ITicker.cpp                 \
				ICompleter.cpp              \
				IClock.cpp                  \
				Timeline.cpp                \
				Ticker.cpp                  \
				ITweenForm.cpp              \
				LinearTweenForm.cpp         \
				Tween.cpp
LIB         = libbetweener.so
INCLUDEDIRS =
LIBDIRS     =
OBJECTS     = $(SOURCES:.cpp=.o)
HEADERS     = $(SOURCES:.cpp=.h)
DEBUG       = -g
CXXFLAGS    = -Wall -Werror -ansi $(DEBUG) $(INCLUDEDIRS)
CXX         = g++
CLANG       = clang
                  
all: $(LIB)      
                  
$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CXX) -fPIC  $(CXXFLAGS) -c $(*:=.cpp) -o $(*:=.o)

$(LIB): $(OBJECTS)
	$(CXX) -shared -Wl,-soname,$(LIB) -o $(LIB) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(LIB) *.plist

analyze: all
	$(CLANG) --analyze *.cpp

# -Weffc++ 
