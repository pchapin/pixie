#
# Makefile for the Pixie project.
#

CXX=g++
CXXFLAGS=-std=c++20 -c -O -I../SpicaCpp
LINK=g++
LINKFLAGS=
SOURCES=main.cpp   \
	Tasks.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=pixie
LIBSPICA=../SpicaCpp/libSpicaCpp.a

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXECUTABLE):	$(OBJECTS)
	$(CXX) $(OBJECTS) $(LIBSPICA) $(LINKFLAGS) -o $@

# File Dependencies
###################

main.o:		main.cpp Tasks.hpp ../SpicaCpp/Date.hpp

Tasks.o:	Tasks.cpp Tasks.hpp ../SpicaCpp/Date.hpp 

# Additional Rules
##################
clean:
	rm -f *.bc *.bc1 *.bc2 *.o $(EXECUTABLE) *.s *.ll *~
