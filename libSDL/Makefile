NAME	:= libSDL.so

CC		:= clang++
CFLAGS	:= -shared -fPIC -lSDL2 -lSDL2_image -lSDL2_ttf -Wall -Werror -Wextra

DEPS	:= ../inc/IGraph.hpp SDLGraph.hpp 
SRCS	:= SDLGraph.cpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $@ $^ -I ~/.brew/include -L ~/.brew/lib -fsanitize=address 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all