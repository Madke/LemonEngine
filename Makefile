OBJS =  glad.c main.cpp SDL_platform.cpp application.cpp controls.cpp

OBJ_NAME = engine.app

all: $(OBJS)
	clang++ -std=c++11 $(OBJS) -lSDL2 -o $(OBJ_NAME)

Debug: $(OBJS)
	clang++ -std=c++11 $(OBJS) -lSDL2 -o $(OBJ_NAME)

Run: $(OBJ_NAME)
	$(OBJ_NAME)
