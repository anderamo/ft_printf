/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 10:36:10 by aamorin-          #+#    #+#             */
/*   Updated: 2021/06/28 11:56:51 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*check_specifier(char *spe, char *full_flags)
{
	char	*str;
	size_t	len;

	len = ft_strlen(full_flags);
	str = malloc(len + 1 + 1);
	str = ft_strdup(full_flags);
	free(full_flags);
	if (spe[len] == 'c' || spe[len] == 's' || spe[len] == 'p'
		|| spe[len] == 'i' || spe[len] == 'u' || spe[len] == 'x'
		|| spe[len] == 'X' || spe[len] == '%')
	{
		str[len] = spe[len];
		str[len + 1] = '\0';
	}
	return (str);
}

char	*check_precision(char *precision, char *full_flags)
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

char	*check_width(char *width, char *full_flags)
{
	char	*str;
	size_t	len;

	len = ft_strlen(full_flags);
	str = malloc(len + 1 + 1);
	str = ft_strdup(full_flags);
	free(full_flags);
	if (width[len] == '*')
	{
		str[len] = width[len];
		str[len + 1] = '\0';
	}
	return (str);
}

char	*check_flag(char *flag, char *full_flags)
{
	int	i;

	full_flags = malloc(1 + 1);
	i = 0;
	if (*flag == '-' || *flag == '+' || *flag == ' '
		|| *flag == '#' || *flag == '0')
	{
		strcpy(full_flags, flag);
		full_flags[i] = *flag;
		full_flags[i + 1] = '\0';
	}
	return (full_flags);
}

char	*check(char *nargs, char *full_flags)
{
	char	*flag;

	flag = ft_strdup((const char *)nargs);
	full_flags = check_flag(flag, full_flags);
	full_flags = check_width(flag, full_flags);
	full_flags = check_precision(flag, full_flags);
	full_flags = check_specifier(flag, full_flags);
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
			flag = check(nargs + 1, NULL);
			item_count++;
			if (flag == NULL)
			{
				printf("entro");
			}
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
	char	*str;

	str = "tomate";
	ft_printf("hola%-*w", str);
	return (0);
}
