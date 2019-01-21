CXX = clang++
SDL = -framework SDL2
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
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

# clang++ -I ~/.brew/include -L ~/.brew/lib -lSDL2 -L ~/.brew/lib -lSDL2_image  main.cpp