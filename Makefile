SERVER = server
CLIENT = client
SRCS =	ft_atoi.c	ft_error.c	ft_putchar_fd.c\
		ft_putnbr_fd.c	ft_putstr_fd.c	ft_strlen.c

OBJS = $(SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

HEADER = header.h

.PHONY: all clean fclean re bonus

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJS) server.o $(HEADER)
	cc $(OBJS) server.o -o $(SERVER)

$(CLIENT): $(OBJS) client.o $(HEADER)
	cc $(OBJS) client.o -o $(CLIENT)

%.o: %.c $(HEADER)
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) server.o client.o

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

bonus: $(SERVER) $(CLIENT)