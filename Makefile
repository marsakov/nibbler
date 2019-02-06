# clang++ -I ~/.brew/include -L ~/.brew/lib -lSDL2 -lSDL2_image -lSDL2_ttf main.cpp SDLGraph.cpp
# clang++ -I ~/.brew/include -L ~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-system -rpath ~/.brew/lib main.cpp SFMLGraph.cpp



# g++ -shared -fPIC src/SFMLGraph.cpp -o libSFML.so -I ~/.brew/include -L ~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-system -rpath ~/.brew/lib
# g++ -shared -fPIC src/SDLGraph.cpp -o libSDL.so -I ~/.brew/include -L ~/.brew/lib -lSDL2 -lSDL2_image -lSDL2_ttf
# g++ src/main.cpp src/Snake.cpp]


NAME	:= nibbler

CC		:= clang++
CFLAGS	:= #-Wall -Werror -Wextra

DEPS	:= inc/IGraph.hpp inc/Game.hpp inc/Rect.hpp inc/Snake.hpp
SRCS	:= src/Game.cpp src/Snake.cpp src/main.cpp
OBJS	:= $(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	g++ -shared -fPIC src/SFMLGraph.cpp -o libSFML.so -I ~/.brew/include -L ~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-system -rpath ~/.brew/lib
	g++ -shared -fPIC src/SDLGraph.cpp -o libSDL.so -I ~/.brew/include -L ~/.brew/lib -lSDL2 -lSDL2_image -lSDL2_ttf
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all