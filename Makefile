OFILES=main.o 


# where to find .h files
IFLAGS=-I../ -I../glfw/include
CFLAGS=-DGL_GLEXT_PROTOTYPES -Wall

# detect os and set flags accordingly
UNAME := $(shell uname)

# For linux. Uses local glfw for now
ifeq ($(UNAME), Linux)
LIB=../glfw/lib/x11/libglfw.a
LDFLAGS= $(LIB) -lXxf86vm -lXext  -lrt -lX11 -lGLU -lGL -pthread -lm 
endif


# For OS X
ifeq ($(UNAME), Darwin)
LDFLAGS=-lglfw -framework Cocoa -framework OpenGL -framework IOKit
endif


all: $(OFILES)
	g++ $(OFILES) -o kpp $(LDFLAGS) 
	

%.o: %.cpp
	g++ -c $(CFLAGS) $(IFLAGS) -o $@ $<




# Comment this out
ifeq ("x", "y")
main.o: main.cpp
	g++ -c main.cpp

GLSL_helper.o: GLSL_helper.cpp
	g++ -c GLSL_helper.cpp
	
MStackHelp.o: MStackHelp.cpp
	g++ -c MStackHelp.cpp
	
BBObject.o: BBObject.cpp
	g++ -c BBObject.cpp
	
BBMatObject.o: BBMatObject.cpp
	g++ -c BBMatObject.cpp
	
BBCamera.o: BBCamera.cpp
	g++ -c BBCamera.cpp
	
BBPlayerObject.o: BBPlayerObject.cpp
	g++ -c BBPlayerObject.cpp
	
BBAvoidObject.o: BBAvoidObject.cpp
	g++ -c BBAvoidObject.cpp
	
BBCollectObject.o: BBCollectObject.cpp
	g++ -c BBCollectObject.cpp
	
BBLight.o: BBLight.cpp
	g++ -c BBLight.cpp

endif
