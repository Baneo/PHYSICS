CC=g++
GLUTFLAGS=-lGL -lGLU -lglut

INCLUDES=inc.h timing.h app.h vector3D.h
CPPFILES=testApp1.cpp timing.cpp app.cpp vector3D.cpp
EXECNAME=testApp1

main: 
	$(CC) $(CPPFILES) -g -o $(EXECNAME) $(GLUTFLAGS)

clean:
	rm -rf $(EXECNAME)

run:
	./$(EXECNAME)
