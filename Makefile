NAME	:= nibbler

CC		:= clang++
CFLAGS	:= #-Wall -Werror -Wextra

DEPS	:= inc/IGraph.hpp inc/Game.hpp inc/Rect.hpp inc/Snake.hpp inc/Network.hpp
SRCS	:= src/Game.cpp src/Snake.cpp src/Network.cpp src/main.cpp
OBJS	:= $(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libOpenGL
	make -C libSDL
	make -C libSFML
	make -C libSFMLSound
	$(CC) $(CFLAGS) -o $@ $^ -fsanitize=address 

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make fclean -C libOpenGL
	make fclean -C libSDL
	make fclean -C libSFML
	make fclean -C libSFMLSound	

re: fclean all