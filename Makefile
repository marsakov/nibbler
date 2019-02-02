CXX = clang++
SDL = -framework SDL2
CXXFLAGS = -Wall -c -std=c++11
LDFLAGS = $(SDL)
EXE = SDL_Lesson0

all: $(EXE)


$(EXE): main.o

	$(CXX) $(LDFLAGS) $< -o $@

main.o: main.cpp

	$(CXX) $(CXXFLAGS) $< -o $@

clean:

	rm *.o && rm $(EXE)


# clang++ -I ~/.brew/include -L ~/.brew/lib -lSDL2 -lSDL2_image -lSDL2_ttf main.cpp SDLGraph.cpp
# clang++ -I ~/.brew/include -L ~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-system -rpath ~/.brew/lib main.cpp SFMLGraph.cpp



# g++ -shared -fPIC src/SFMLGraph.cpp -o libSFML.so -I ~/.brew/include -L ~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-system -rpath ~/.brew/lib
# g++ -shared -fPIC src/SDLGraph.cpp -o libSDL.so -I ~/.brew/include -L ~/.brew/lib -lSDL2 -lSDL2_image -lSDL2_ttf
# g++ src/main.cpp src/Snake.cpp