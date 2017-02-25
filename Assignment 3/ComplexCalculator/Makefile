# Makefile for ECE3090 Complex Calculator Assignment
# George F. Riley

CXX=g++

calculator:	calculator.o complex.o string-parse.o
	@echo Linking calculator
	$(CXX) -o calculator calculator.o complex.o string-parse.o

clean:
	rm -f calculator calculator.o complex.o string-parse.o
	@echo Cleaned!


