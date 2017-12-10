CC=g++
GLUTFLAGS=-lGL -lGLU -lglut

INCLUDES=inc.h timing.h app.h vector3D.h particle.h 
CPPFIREWORK=firework.cpp timing.cpp vector3D.cpp app.cpp particle.cpp
CPPPEW=pewpew.cpp timing.cpp vector3D.cpp app.cpp particle.cpp
EXECNAME=firework
PEWNAME=pewpew

all: pewpew firework

firework: 
	$(CC) $(CPPFIREWORK) -g -o $(EXECNAME) $(GLUTFLAGS)

pewpew: 
	$(CC) $(CPPPEW) -g -o $(PEWNAME) $(GLUTFLAGS)

.PHONY: clean 

clean:
	rm -rf $(EXECNAME) $(PEWNAME)

runfirework:
	./$(EXECNAME)

runpewpew:
	./$(PEWNAME)	 
