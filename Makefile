
OFILES=main.o MStackHelp.o GLSL_helper.o Shader.o \
	ModelManager.o GameObject.o GameDrawableObject.o \
	GameKartObject.o GameRamp.o GameUpgradeObject.o GamePhysicalObject.o

# where to find .h files
IFLAGS=-I./glfw/include 
CFLAGS=-DGL_GLEXT_PROTOTYPES -Wall -g

# detect os and set flags accordingly
UNAME := $(shell uname)


# For linux. Uses local glfw for now
ifeq ($(UNAME), Linux)
	LIB=./glfw/lib/x11/libglfw.a 

	# -lXrandr for csl
	ifeq ($(shell uname -n), pack-nasa)
		XRANDR=
	else
		XRANDR=-lXrandr
	endif

    # uncomment to not compile with sound, and not use any real sound
    # CFLAGS += -DUSE_DUMMY_SOUND

    # uncomment to compile with sdl_mixer for sound
    LIB += -lSDL_mixer

    IFLAGS += -I/usr/include/SDL

LDFLAGS= $(LIB) -lXxf86vm -lXext  -lrt -lX11 -lGLU -lGL -pthread -lm $(XRANDR)
endif


# For OS X
ifeq ($(UNAME), Darwin)

    # uncomment to not compile with sound, and not use any real sound
    #CFLAGS += -DUSE_DUMMY_SOUND

    IFLAGS += -I/Library/Frameworks/SDL_mixer.framework/Headers \
	-I/Library/Frameworks/SDL.framework/Headers

    LDFLAGS=-lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework SDL_mixer -framework SDL

endif



all: build

build: $(OFILES)
	g++ $(CFLAGS) $(OFILES) -o kpp $(LDFLAGS)

%.o: %.cpp
	g++ -c $(CFLAGS) $(IFLAGS) -o $@ $<

clean:
	rm -rf *.o kpp



# Comment this out
# that stuff is still in makefile2
