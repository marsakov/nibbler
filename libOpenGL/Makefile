NAME	:= libOpenGL.so

CC		:= clang++
CFLAGS	:= -shared -fPIC -framework GLUT -framework OpenGL -lSDL2 -Wno-deprecated-declarations -Wall -Werror -Wextra

DEPS	:= ../inc/IGraph.hpp OpenGLGraph.hpp 
SRCS	:= OpenGLGraph.cpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $@ $^ -I ~/.brew/include -L ~/.brew/lib -fsanitize=address 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all