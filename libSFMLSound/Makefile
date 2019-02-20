NAME	:= libSFMLSound.so

CC		:= clang++
CFLAGS	:= -shared -fPIC -I ~/.brew/include -L ~/.brew/lib -lsfml-audio -lsfml-system -rpath ~/.brew/lib -rpath ~/.brew/lib #-Wall -Werror -Wextra

DEPS	:= ISound.hpp SoundSFML.hpp
SRCS	:= SoundSFML.cpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $@ $^ -I ~/.brew/include -L ~/.brew/lib -fsanitize=address 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all