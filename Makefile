CC=g++
GLUTFLAGS=-lGL -lGLU -lglut
INCLUDES=inc.h
CPPFILES=gluTest.cpp
EXECNAME=TestGlut

main: 
	$(CC) -g -o $(EXECNAME) $(CPPFILES) $(INCLUDES) $(GLUTFLAGS)

clean:
	rm -rf $(EXECNAME)

run:
	./$(EXECNAME)
