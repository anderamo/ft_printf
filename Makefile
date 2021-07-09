
NAME	= libftprintf.a

SRCS	=	ft_printf.c\
			libft/ft_strlen.c\
			libft/ft_strlcpy.c\
			libft/ft_strlcat.c\
			libft/ft_strncmp.c\
			libft/ft_atoi.c\
			libft/ft_isalpha.c\
			libft/ft_isprint.c\
			libft/ft_isdigit.c\
			libft/ft_isalnum.c\
			libft/ft_toupper.c\
			libft/ft_tolower.c\
			libft/ft_memset.c\
			libft/ft_bzero.c\
			libft/ft_memcpy.c\
			libft/ft_memccpy.c\
			libft/ft_memchr.c\
			libft/ft_memcmp.c\
			libft/ft_strnstr.c\
			libft/ft_strchr.c\
			libft/ft_strrchr.c\
			libft/ft_memmove.c\
			libft/ft_isascii.c\
			libft/ft_calloc.c\
			libft/ft_strdup.c\
			libft/ft_substr.c\
			libft/ft_strjoin.c\
			libft/ft_strtrim.c\
			libft/ft_split.c\
			libft/ft_itoa.c\
			libft/ft_strmapi.c

OBJ = $(SRCS:.c=.o)

INC = ./includes

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o:%.c
	gcc -c $(FLAGS) -I $(INC) $< -o $@

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
