/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 10:36:10 by aamorin-          #+#    #+#             */
/*   Updated: 2021/07/06 16:42:56 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

typedef struct s_flags
{
	int		dot;
	int		minus;
	int		asterisk;
	int		zero;
	int		plus;
	int		dot_asterisk;
	char	type;
	int		numbers;
}	t_flags;

t_flags	initialize_list(void)
{
	t_flags	flags;

	flags.dot = -1;
	flags.numbers = -1;
	flags.minus = -1;
	flags.asterisk = -1;
	flags.zero = -1;
	flags.plus = -1;
	return (flags);
}

int	get_flags_number(char *flag)
{
	size_t		i;
	size_t		j;
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
	return (ft_atoi(number));
}

char	*get_number(char *flag, char *full_flags)
{
	char	*str;
	size_t	len;

	if (full_flags)
	{
		len = ft_strlen(full_flags);
		str = malloc(len + 1 + 1);
		str = ft_strdup(full_flags);
	}
	else
	{
		len = 0;
		while (flag[len] >= '0' && flag[len] <= '9')
			len++;
		str = malloc(len + 1 + 1);
		len = 0;
	}
	free(full_flags);
	while (flag[len] >= '0' && flag[len] <= '9')
	{
		str[len] = flag[len];
		len++;
	}
	str[len + 1] = '\0';
	return (str);
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

t_flags	check(char *flags, va_list ap)
{
	t_flags	all_flags;

	all_flags = initialize_list();
	if (*flags > '0' && *flags <= '9')
		all_flags.numbers = get_flags_number(flags);
	if (*flags == '0')
		all_flags.zero = get_flags_number(flags + 1);
	if (*flags == '-')
		all_flags.minus = get_flags_number(flags + 1);
	if (*flags == '*')
			all_flags.asterisk = va_arg (ap, unsigned int);
	if (*flags == '.')
	{
		flags++;
		if (*flags == '*')
			all_flags.dot = va_arg (ap, unsigned int);
		else
			all_flags.dot = get_flags_number(flags);
	}
	while (*flags)
		flags++;
	flags--;
	all_flags.type = get_type(*flags);
	return (all_flags);
}

char	*get_specifier(char *spe, char *full_flags)
{
	char	*str;
	size_t	len;

	len = ft_strlen(full_flags);
	str = malloc(len + 1 + 1);
	str = ft_strdup(full_flags);
	free(full_flags);
	if (spe[len] == 'c' || spe[len] == 's' || spe[len] == 'p'
		|| spe[len] == 'd' || spe[len] == 'i' || spe[len] == 'u'
		|| spe[len] == 'x' || spe[len] == 'X' || spe[len] == '%')
	{
		str[len] = spe[len];
		str[len + 1] = '\0';
	}
	else
		printf("ERROR_GET_SPECIFIER");
	return (str);
}

char	*get_width(char *width, char *full_flags)
{
	char	*str;
	size_t	len;

	len = ft_strlen(full_flags);
	str = malloc(len + 1 + 1);
	str = ft_strdup(full_flags);
	free(full_flags);
	if (width[len - 1] > '0' && width[len - 1] <= '9' && width[len] == '*')
	{
		printf("ERROR_GET_WIDTH");
		return (str);
	}
	if (width[len] == '*')
	{
		str[len] = width[len];
		str[len + 1] = '\0';
	}
	return (str);
}

char	*get_flag(char *flag, char *full_flags)
{
	int	i;

	if (*flag > '0' && *flag <= '9')
		full_flags = get_number(flag, full_flags);
	else
	{
		full_flags = malloc(1 + 1);
		i = 0;
		if (*flag == '-' || *flag == '+' || *flag == '.'
			|| *flag == '#' || *flag == '0')
		{
			strcpy(full_flags, flag);
			full_flags[i] = *flag;
			full_flags[i + 1] = '\0';
		}
	}
	return (full_flags);
}

char	*get(char *nargs, char *full_flags)
{
	char	*flag;

	flag = ft_strdup((const char *)nargs);
	full_flags = get_flag(flag, full_flags);
	if (*full_flags == '-' || *full_flags == '0' || *full_flags == '.')
		full_flags = get_number(flag, full_flags);
	full_flags = get_width(flag, full_flags);
	full_flags = get_specifier(flag, full_flags);
	free(flag);
	return (full_flags);
}
void	write_para_string(t_flags flags_list, char *nargs, va_list ap)
{
	char	*string;
	int		i;

	string = va_arg (ap, char *);
	i = ft_strlen(string);
	while ((flags_list.numbers > i++ && flags_list.numbers != -1)
			|| flags_list.asterisk > i++ && flags_list.asterisk != -1)
			write (1, " ", 1);
	i = ft_strlen(string);
	while (flags_list.zero > i++ && flags_list.zero != -1)
		write (1, "0", 1);
	if (flags_list.dot != -1 && i > flags_list.dot)
		write (1, string, flags_list.dot);
	else
		write (1, string, ft_strlen(string));
	i = ft_strlen(string);
	while (flags_list.minus > i++ && flags_list.minus != -1)
		write (1, " ", 1);
}

void	write_parameters(t_flags flags_list, char *nargs, va_list ap)
{
	if (flags_list.type == 's')
		write_para_string(flags_list, nargs, ap);
}

void	ft_printf(char *nargs, ...)
{
	va_list	ap;
	t_flags	flags_list;
	int		item_count;
	char	*flag;
	char	*string;

	va_start (ap, nargs);
	item_count = 0;
	while (*nargs)
	{
		if (*nargs == '%')
		{
			flag = get(nargs + 1, NULL);
			item_count++;
			//printf("\nFull flags %d = %s\n", item_count, flag);
			if (flag != NULL)
			{
				flags_list = check(flag, ap);
				nargs = nargs + ft_strlen(flag);
				write_parameters(flags_list, nargs, ap);

				/*
				string = va_arg (ap, char *);
				write (1, string, ft_strlen(string));
				printf("flags_list.numbers = %d\n", flags_list.numbers);
				printf("flags_list.minus = %d\n", flags_list.minus);
				printf("flags_list.dot = %d\n", flags_list.dot);
				printf("flags_list.asterisk = %d\n", flags_list.asterisk);
				printf("flags_list.dot_asterisk = %d\n", flags_list.dot_asterisk);
				printf("flags_list.zero = %d\n", flags_list.zero);
				printf("flags_list.type = %s\n", flags_list.type);
				*/
			}
		}
		else
		{
			write(1, nargs, 1);
		}
		nargs++;
	}
	va_end (ap);
}

int	main(int argc, char *argv[])
{
	char	*str2;
	char	*str1;

	str1 = "tomate";
	str2 = "volador";
	ft_printf("hola %*s", -1, str1);
	return (0);
}
/*
//full_flags = get_precision(flag, full_flags);
char	*get_precision(char *precision, char *full_flags)
{
	char	*str;
	size_t	len;

	len = ft_strlen(full_flags);
	str = malloc(len + 1 + 1);
	str = ft_strdup(full_flags);
	free(full_flags);
	if (precision[len] == '.')
	{
		str[len] = precision[len];
		len++;
		if (precision[len] == '*')
		{
			str[len] = precision[len];
			len++;
		}
		str[len] = '\0';
	}
	return (str);
}
*/
