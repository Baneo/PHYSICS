CC=g++
GLUTFLAGS=-lGL -lGLU -lglut

INCLUDES=inc.h timing.h app.h vector3D.h particle.h 
CPPFILES=testFirework.cpp timing.cpp vector3D.cpp app.cpp particle.cpp
EXECNAME=testFirework

main: 
	$(CC) $(CPPFILES) -g -o $(EXECNAME) $(GLUTFLAGS)

clean:
	rm -rf $(EXECNAME)

run:
	./$(EXECNAME)
