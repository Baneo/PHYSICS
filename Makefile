CC=g++
GLUTFLAGS=-lGL -lGLU -lglut

INCLUDES=inc.h timing.h app.h vector3D.h particle.h
CPPFILES=testFirework.cpp timing.cpp app.cpp vector3D.cpp particle.cpp
EXECNAME=testFirework

main: 
	$(CC) $(CPPFILES) -g -o $(EXECNAME) $(GLUTFLAGS)

clean:
	rm -rf $(EXECNAME)

run:
	./$(EXECNAME)
