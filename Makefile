EXECUTABLE = swpathtracer

CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic

ifeq ($(DEBUG), 1)
CXXFLAGS += -DDEBUG -O0 -g3
else
CXXFLAGS += -DNDEBUG -O3 -g0
endif

CPPFLAGS += -MMD \
			-I/usr/local/Cellar/glm/0.9.8.3 \
			-I/usr/local/Cellar/imagemagick/7.0.5-4/include/ImageMagick-7/ \
			-I/usr/local/include \
			-I.

LDFLAGS = -L/usr/lib/gcc/x86_64-linux-gnu/4.8 \
		  -L/usr/lib/x86_64-linux-gnu \
		  -L/usr/lib \
		  -L/usr/local/lib \
		  -L.

LDLIBS = -lassimp

SOURCES = $(wildcard *.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDLIBS) Magick++-config

.cpp.o:

-include $(OBJECTS:.o=.d)

.PHONY: clean distclean

clean:
	rm *.o *.d

distclean: clean
	rm $(EXECUTABLE)
