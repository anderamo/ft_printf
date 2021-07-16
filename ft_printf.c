/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 10:36:10 by aamorin-          #+#    #+#             */
/*   Updated: 2021/07/16 12:47:46 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

t_flags	initialize_list(void)
{
	t_flags	flags;

	flags.dot_w = -1;
	flags.dot_f = -1;
	flags.numbers = -1;
	flags.minus = -1;
	flags.zero = -1;
	flags.plus = -1;
	flags.negative = 0;
	return (flags);
}

int	ft_putstr_count(char c, int n)
{
	int	i;

	i = 0;
	while (n > i)
	{
		write(1, &c ,1);
		i++;
	}
	return (i);
}

int	ft_putchar_count(char c)
{
	write(1, &c ,1);
	return (1);
}

int	ft_putstring_count(char *str, int n)
{
	write(1, str, n);
	return (n);
}

int	get_flags_number(char *flag)
{
	size_t		i;
	size_t		j;
	size_t		n;
	char		*number;

	i = 0;
	j = 0;
	while (flag[i] >= '0' && flag[i] <= '9')
		i++;
	if (i == 0)
		return (0);
	number = malloc(i + 1);
	while (flag[j] >= '0' && flag[j] <= '9')
	{
		number[j] = flag[j];
		j++;
	}
	number[j] = '\0';
	n = ft_atoi(number);
	free(number);
	return (n);
}

char	get_type(char type)
{
	if (type == 'd' || type == 'i')
		return ('d');
	if (type == 's')
		return ('s');
	if (type == 'c')
		return ('c');
	if (type == 'p')
		return ('p');
	if (type == 'u')
		return ('u');
	return (0);
}

t_flags	check(char *flags)
{
	t_flags	all_flags;

	all_flags = initialize_list();
	if (*flags > '0' && *flags <= '9')
		all_flags.numbers = get_flags_number(flags);
	if (*flags == '0')
		all_flags.zero = get_flags_number(flags + 1);
	if (*flags == '-')
		all_flags.minus = get_flags_number(flags + 1);
	if (*flags == '.')
		all_flags.dot_f = get_flags_number(flags + 1);
	while (*flags)
	{
		flags++;
		if (*flags == '.')
		{
			all_flags.dot_w = get_flags_number(flags + 1);
			if (all_flags.dot_w == 0 && all_flags.minus != -1)
				all_flags.dot_w = 1;
		}
	}
	flags--;
	all_flags.type = get_type(*flags);
	return (all_flags);
}

char	*get_specifier(char *spe, char *full_flags)
{
	char	*str;
	size_t	len;
	char	*join;

	len = 0;
	if (full_flags)
		len = ft_strlen(full_flags);
	if (spe[len] == 'c' || spe[len] == 's' || spe[len] == 'p'
		|| spe[len] == 'd' || spe[len] == 'i' || spe[len] == 'u'
		|| spe[len] == 'x' || spe[len] == 'X' || spe[len] == '%')
	{
		str = malloc(1 + 1);
		str[0] = spe[len];
		str[1] = '\0';
		len++;
		join = ft_strjoin(full_flags, str);
		free(str);
		return (join);
	}
	return (full_flags);

}

char	*get_number(char *flag, char *full_flags)
{
	char	*str;
	size_t	len;
	size_t	i;
	char	*join;

	i = 0;
	len = 0;


	if (full_flags)
		len = ft_strlen(full_flags);
	while (flag[len] >= '0' && flag[len] <= '9')
			len++;
	str = malloc(len + 1);
	if (full_flags)
		len = ft_strlen(full_flags);
	else
		len = 0;
	while (flag[len] >= '0' && flag[len] <= '9')
	{
		str[i] = flag[len];
		len++;
		i++;
	}
	str[i] = '\0';
	join = ft_strjoin(full_flags, str);
	free(str);
	return (join);
}

char	*get_precision(char *precision, char *full_flags)
{
	char	*str;
	size_t	len;
	char	*join;

	if (full_flags)
		len = ft_strlen(full_flags);
	else
		len = 0;
	if (precision[len] == '.')
	{
		str = malloc(1 + 1);
		str[0] = precision[len];
		str[1] = '\0';
		join = malloc(len + ft_strlen(str));
		join = ft_strjoin(full_flags, str);
		free(str);
		return (join);
	}
	str = ft_strdup(full_flags);
	free(full_flags);
	return (str);
}

char	*get_flag(char *flag)
{
	char	*str;
	int i;

	i = 0;
	if (*flag > '0' && *flag <= '9')
	{
		str = get_number(flag, NULL);
	}
	else
	{
		str = malloc(1 + 1);
		if (*flag == '-' || *flag == '+' || *flag == '.'
			|| *flag == '#' || *flag == '0')
		{

			str[i] = *flag;
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

char	*get(char *nargs, char *full_flags)
{
	char	*flag;

	flag = ft_strdup((const char *)nargs);
	full_flags = get_flag(flag);

	if (*full_flags == '-' || *full_flags == '0' || *full_flags == '.'
		|| *full_flags == '+')
		full_flags = get_number(flag, full_flags);
	if (*full_flags != '.')
	{
		full_flags = get_precision(flag, full_flags);
		if (*full_flags == '.')
			full_flags = get_number(flag, full_flags);
	}
	full_flags = get_specifier(flag, full_flags);
	free(flag);
	return (full_flags);
}

int	dot_string (t_flags flags_list, char *string, int count, int i)
{
	if (flags_list.numbers != -1)
		count += ft_putstr_count(' ', flags_list.numbers - (flags_list.dot_w - i) - i);
	if (flags_list.dot_w > -1 && i > flags_list.dot_w)
		count += ft_putstring_count(string, flags_list.dot_w);
	else
		count += ft_putstring_count(string, i);
	if (flags_list.minus != -1)
	{
		count += ft_putstr_count(' ', flags_list.minus - (flags_list.dot_w - i) - i);
	}
	return (count);
}

int	write_para_string(t_flags flags_list, va_list ap)
{
	char	*string;
	int		i;
	int		count;

	count = 0;
	string = va_arg (ap, char *);
	i = ft_strlen(string);
	if (flags_list.dot_w != -1)
	{
		count += dot_string(flags_list, string, count, i);
	}
	else if (flags_list.dot_f == -1)
	{
		while (flags_list.numbers-- > i && flags_list.numbers != -1)
			count += ft_putstr_count(' ', 1);
		while (flags_list.zero-- > i && flags_list.zero != -1)
			count += ft_putstr_count('0', 1);
		if (flags_list.dot_f > -1 && i > flags_list.dot_f)
			count += ft_putstring_count(string, flags_list.dot_f);
		else
			count += ft_putstring_count(string, i);
		if (flags_list.minus != -1)
			count += ft_putstr_count(' ', flags_list.minus - i);
		return (count);
	}
	return (count);
}

int	write_para_character(t_flags flags_list, va_list ap)
{
	unsigned char chr;
	int		count;

	count = 0;
	chr = va_arg (ap, int);
	while (flags_list.numbers-- > 1 && flags_list.numbers != -1)
		count += ft_putstr_count(' ', 1);
	count += ft_putstr_count(chr, 1);
	while (flags_list.minus-- > 1 && flags_list.minus != -1)
		count += ft_putstr_count(' ', 1);
	return (count);
}

int	dot_integer (t_flags flags_list, char *num_char, int count, size_t i)
{
	if (flags_list.numbers != -1)
		count += ft_putstr_count(' ', flags_list.numbers - (flags_list.dot_w - i) - i - flags_list.negative);
	if (flags_list.zero != -1)
	{
		if (flags_list.dot_w != 0)
			count += ft_putstr_count(' ', flags_list.zero - (flags_list.dot_w - i) - i - flags_list.negative);
		else if (flags_list.dot_w == 0 && flags_list.negative == 1)
			count += ft_putstr_count(' ', flags_list.zero - i - flags_list.negative);
		else
			count += ft_putstr_count(' ', flags_list.zero);
	}
	if (flags_list.negative == 1)
			count += ft_putchar_count('-');
	if (flags_list.dot_w != -1)
		count += ft_putstr_count('0', flags_list.dot_w - i);
	if (flags_list.dot_w != 0 || (flags_list.dot_w == 0 && flags_list.negative == 1))
		count += ft_putstring_count(num_char, i);
	if (flags_list.minus != 0)
	{
		flags_list.minus -=	flags_list.dot_w - i;
		count += ft_putstr_count(' ', flags_list.minus - i - flags_list.negative);
	}
	return (count);
}

int	dot_flag_write (t_flags flags_list, char *num_char, int count, size_t i)
{
	while (flags_list.dot_f > i++)
		count += ft_putstr_count('0', 1);
	if (flags_list.dot_f != -1 && ft_strcmp(num_char, "0") != 0)
		count += ft_putstring_count(num_char, ft_strlen(num_char));
	return (count);
}

int	write_para_integer(t_flags flags_list, va_list ap, int number)
{
	char	*num_char;
	int		i;
	int		count;

	count = 0;
	if (number < 0 && number < INT_MIN)
	{
		flags_list.negative = 1;
		number = number * -1;

	}
	num_char = ft_itoa(number);
	i = ft_strlen(num_char);
	if (flags_list.dot_f != -1)
		count += dot_flag_write(flags_list, num_char, count, i);
	if (flags_list.dot_w != -1)
	{
		count += dot_integer(flags_list, num_char, count, i);
	}
	else if (flags_list.dot_f == -1)
	{
		if (flags_list.numbers != -1)
			count += ft_putstr_count(' ', flags_list.numbers - i);
		if (flags_list.negative == 1)
			count += ft_putchar_count('-');
		while (flags_list.zero-- > i && flags_list.zero != -1)
			count += ft_putstr_count('0', 1);
		count += ft_putstring_count(num_char, ft_strlen(num_char));
		if (flags_list.minus != -1)
			count += ft_putstr_count(' ', flags_list.minus - i);
	}
	free(num_char);
	return (count);
}

int	write_parameters(t_flags flags_list, va_list ap)
{
	if (flags_list.type == 's')
		return(write_para_string(flags_list, ap));
	if (flags_list.type == 'c')
		return(write_para_character(flags_list, ap));
	if (flags_list.type == 'i' || flags_list.type == 'd')
		return(write_para_integer(flags_list, ap, va_arg (ap, int)));
	return (0);
}

int	ft_printf(const char *nargs, ...)
{
	va_list	ap;
	t_flags	flags_list;
	int		count;
	char	*flag;

	count = 0;
	va_start (ap, nargs);
	while (*nargs)
	{
		if (*nargs == '%')
		{
			flag = get((char *)nargs + 1, NULL);
			if (flag != NULL)
			{
				flags_list = check(flag);
				nargs = nargs + ft_strlen(flag) + 1;
				//printf("0x7f9097405830 = %s\n", flag);
				count += write_parameters(flags_list, ap);
				free(flag);
/*
				printf("flags_list.numbers = %d\n", flags_list.numbers);
				printf("flags_list.negative = %d\n", flags_list.negative);
				printf("flags_list.minus = %d\n", flags_list.minus);
				printf("flags_list.dot_w = %d\n", flags_list.dot_w);
				printf("flags_list.dot_f = %d\n", flags_list.dot_f);
				printf("flags_list.zero = %d\n", flags_list.zero);
				printf("flags_list.type = %c\n", flags_list.type);
*/
			}
		}
		else
		{
			count += ft_putchar_count(*nargs);
			nargs++;
		}
	}
	va_end (ap);
	return (count);
}

