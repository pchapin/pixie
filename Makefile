#
# Makefile for the Pixie project.
#

CXX=g++
CXXFLAGS=-std=c++11 -c -O -I../Spica/Cpp
LINK=g++
LINKFLAGS=
SOURCES=main.cpp   \
	Tasks.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=pixie
LIBSPICA=../Spica/Cpp/libSpicaCpp.a

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXECUTABLE):	$(OBJECTS)
	$(CXX) $(OBJECTS) $(LIBSPICA) $(LINKFLAGS) -o $@

# File Dependencies
###################

main.o:		main.cpp Tasks.hpp ../Spica/Cpp/Date.hpp

Tasks.o:	Tasks.cpp Tasks.hpp ../Spica/Cpp/Date.hpp 

# Additional Rules
##################
clean:
	rm -f *.bc *.bc1 *.bc2 *.o $(EXECUTABLE) *.s *.ll *~
