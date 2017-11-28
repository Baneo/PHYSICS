CC=g++
GLUTFLAGS=-lGL -lGLU -lglut
INCLUDES=inc.h app.h timing.h
CPPFILES=testApp1.cpp
EXECNAME=testApp1

main: 
	$(CC) -g -o $(EXECNAME) $(CPPFILES) $(INCLUDES) $(GLUTFLAGS)

clean:
	rm -rf $(EXECNAME)

run:
	./$(EXECNAME)