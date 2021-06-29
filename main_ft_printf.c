/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 10:36:10 by aamorin-          #+#    #+#             */
/*   Updated: 2021/06/29 11:58:00 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

typedef struct s_flags
{
	int	dot;
	int	minus;
	int	asterisk;
	int	zero;
	int	plus;
	int	dot_asterisk;
	int	type;
}	t_flags;

t_flags	initialize(void)
{
	t_flags	flags;

	flags.dot = -1;
	flags.minus = -1;
	flags.asterisk = -1;
	flags.zero = -1;
	flags.dot_asterisk = -1;
	flags.type = -1;
	flags.plus = -1;
	return (flags);
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
		while (flag[len] > '0' && flag[len] <= '9')
			len++;
		str = malloc(len + 1 + 1);
		len = 0;
	}
	free(full_flags);
	while (flag[len] > '0' && flag[len] <= '9')
	{
		str[len] = flag[len];
		len++;
	}
	str[len + 1] = '\0';
	return (str);
}

int	check(char *flags)
{
	t_flags	all_flags;

	while (flags)
	{
		return (0);
	}
	return (0);
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
	//full_flags = get_precision(flag, full_flags);
	full_flags = get_specifier(flag, full_flags);
	printf("\nFull flags = %s\n", full_flags);
	return (full_flags);
}

void	ft_printf(char *nargs, ...)
{
	va_list	ap;
	int		i;
	int		item_count;
	char	*num;
	char	*flag;

	i = 0;
	item_count = 0;
	while (*nargs)
	{
		if (*nargs == '%')
		{
			flag = get(nargs + 1, NULL);
			item_count++;
			if (flag != NULL)
				printf("in");
				//check(flag);
		}
		else
		{
			write(1, nargs, 1);
		}
		nargs++;
		i++;
	}
	printf("\n");
}

int	main(int argc, char *argv[])
{
	char	*str2;
	char	*str1;

	str1 = "tomate";
	str2 = "volador";
	ft_printf("hola %.12d %d", str1, str2);
	return (0);
}
/*
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
