#Notes just in case
#x86_64-w64-mingw32-gcc main.cpp -I/usr/x86_64-w64-mingw32/include/SDL2 -L/usr/x86_64-w64-mingw64/lib -lmingw32 -lSDL2main -lSDL2 -o ./t.exe
#x86_64-w64-mingw32-gcc -o main64.exe main.c
#g++ ./main_test.cpp -lSDL -o bin

CFLAGS  = -O2 -Wall
EXTLIBS = -lSDL2main -lSDL2# -lSDL2_ttf
BINARY  = bin

SRCS = $(shell ls *.cpp)
OBJS = $(SRCS:.cpp=.o)

CROSSCOMPILE = no

### call with make all CROSSCOMPILE=yes to cross compile
### otherwise, assumes a *nix enviornment (tested on OSX and Arch Linux) 
### FIXME: DEPRECATED FOR MINGW BUILD
ifeq ($(CROSSCOMPILE), yes)
	CC = x86_64-w64-mingw32-gcc
	X = .exe
    EXTLIBS = -lmingw32 $(EXTLIBS) 
else
	CC = g++ --std=c++11
	X  = 
endif

all: $(BINARY)

$(BINARY): $(OBJS)
	$(CC) $? $(EXTLIBS) -o $(@)$(X)

$(OBJS): $(SRCS)
	$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(OBJS) $(BINARY)

.PHONY: all clean
