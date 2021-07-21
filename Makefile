

NAME	= libftprintf.a

SRCS	=	ft_printf.c\
			src/get_base.c\
			src/get_flags_list.c\
			src/get_number.c\
			src/get.c\
			src/putchr_c.c\
			src/putstr_c.c\
			src/w_address.c\
			src/w_chr.c\
			src/w_hex_int.c\
			src/w_int.c\
			src/w_string.c\
			src/w_unsint.c\
			src/write_parameters.c\
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
			libft/ft_chrjoin.c\
			libft/ft_strtrim.c\
			libft/ft_split.c\
			libft/ft_itoa.c\
			libft/ft_itoa_unsint.c\
			libft/ft_str_tolower.c\
			libft/ft_strmapi.c\
			libft/ft_strcmp.c

SRCS_1	=	ft_printf_bonus.c\
			src/get_base.c\
			src/get_flags_list.c\
			src/get_number.c\
			src/get.c\
			src/putchr_c.c\
			src/putstr_c.c\
			src/w_address.c\
			src/w_chr.c\
			src/w_hex_int.c\
			src/w_int.c\
			src/w_string.c\
			src/w_unsint.c\
			src/write_parameters.c\
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
			libft/ft_chrjoin.c\
			libft/ft_strtrim.c\
			libft/ft_split.c\
			libft/ft_itoa.c\
			libft/ft_itoa_unsint.c\
			libft/ft_str_tolower.c\
			libft/ft_strmapi.c\
			libft/ft_strcmp.c

OBJ = $(SRCS:.c=.o)

OBJ_1 = $(SRCS_1:.c=.o)

INC = ./includes

FLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

bonus: $(OBJ_1)
	ar rc $(NAME) $(OBJ_1)
	ranlib $(NAME)

%.o:%.c
	gcc -c $(FLAGS) -I $(INC) $< -o $@

clean:
	/bin/rm -f $(OBJ) $(OBJ_1)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean bonus %.o re
