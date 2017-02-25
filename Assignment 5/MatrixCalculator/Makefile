# Rule for making .o from .cc
%.o:	%.cc
	@echo Compiling $*	
	@rm -f $*.o
	$(CXX) $(CXXFLAGS) $(EXTRA_CXXFLAGS) $(EXTRA_INCLUDES) -c $*.cc


.SILENT:
CXX = g++
CXXFLAGS = -g -Wall

all:	matrix-calc test-matrix

matrix-calc:	matrix-calc.o matrix.o string-parse.o
	@echo Linking matrix-calc
	$(CXX) -g -o matrix-calc matrix-calc.o matrix.o string-parse.o

test-matrix:	test-matrix.o matrix.o string-parse.o
	@echo Linking test-matrix
	$(CXX) -g -o test-matrix test-matrix.o matrix.o string-parse.o

matrix-calc.o:	matrix-calc.cc matrix.h string-parse.h

test-matrix.o:	test-matrix.cc matrix.h string-parse.h

matrix.o:	matrix.cc matrix.h string-parse.h

string-parse.o:	string-parse.cc string-parse.h

clean:
	@rm -f *.o matrix-calc

