NAME	:= nibbler

CC		:= clang++
CFLAGS	:= #-Wall -Werror -Wextra

DEPS	:= inc/IGraph.hpp inc/Game.hpp inc/Rect.hpp inc/Snake.hpp
SRCS	:= src/Game.cpp src/Snake.cpp src/main.cpp
OBJS	:= $(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -fsanitize=address 

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all