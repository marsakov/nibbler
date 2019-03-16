NAME	:= libSFML.so

CC		:= clang++
CFLAGS	:= -shared -fPIC -lsfml-graphics -lsfml-window -lsfml-system -rpath ~/.brew/lib -Wall -Werror -Wextra

DEPS	:= ../inc/IGraph.hpp SFMLGraph.hpp 
SRCS	:= SFMLGraph.cpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $@ $^ -I ~/.brew/include -L ~/.brew/lib -fsanitize=address 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all