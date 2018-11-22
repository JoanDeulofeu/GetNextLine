NAME = libft.a

SRC = *.c 

OBJS = *.o

FLAGS = -Wall -Werror -Wextra

all: $(NAME) 

$(NAME): 
		gcc -c $(FLAGS) $(SRC)
		ar rc $(NAME) $(OBJS)

clean:
		rm -f *.o

fclean:	clean
		rm -f *.a

re:	fclean all
