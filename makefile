# Compiler to use
CXX = g++

# Compiler flags to use
CXXFLAGS = -std=c++14 -Wall -g -MMD

# Name of the executable
EXEC = chess

# directory for the bin
BINDIR = ./bin

# Find all cc files in the directory
CCFILES = $(shell find . -name "*.cc")

# Convert all cc files into .o object files
OBJECTS = ${CCFILES:.cc=.o}

# Convert all .o object files to .d dependency files
DEPENDS = ${OBJECTS:.o=.d}

# Linking rule to create the executable
${BINDIR}/${EXEC}: ${OBJECTS}
	mkdir -p ${BINDIR}
	${CXX} ${OBJECTS} -o ${BINDIR}/${EXEC} -lcairo -lX11 

# Compile .cc files to .o files
%.o: %.cc
	${CXX} ${CXXFLAGS} -c $< -o $@

# Include dependency files if they exist
-include ${DEPENDS}

# Phony target ensures 'clean' is always executed
.PHONY: clean

# Clean rule removes executable, object files, and dependency files
clean:
	rm -f ${BINDIR}/${EXEC} ${OBJECTS} ${DEPENDS}
