CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
SERVER	= 	server
CLIENT	=	client 
LIBS	=	-L./libft -lft
LIBFT	=	libft.a

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	@make -C libft

$(SERVER): server.o error.o includes/minitalk.h
	@$(CC) $(FLAGS) server.o error.o $(LIBS) -o $@

$(CLIENT): client.o error.o includes/minitalk.h
	@$(CC) $(FLAGS) client.o error.o $(LIBS) -o $@

%.o: %.c
	@$(CC) $(FLAGS) $< -c -I includes

clean:
	@make clean -C libft
	@rm -rf *.o

fclean: clean
	@make fclean -C libft
	@rm -rf $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re