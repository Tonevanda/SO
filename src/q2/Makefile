NAME = q2

SRCS = q2.c

OBJS =  $(SRCS:.c=.o)

all:	$(NAME)
	$(NAME): $(OBJS)
	gcc -Wall $(OBJS) -o $(NAME)

TMP =  $(SRCS:.c=.c~)

clean:
	$(RM) -f $(OBJS)
	$(RM) -f $(TMP)

fclean: clean
	$(RM) $(NAME)

re: fclean all