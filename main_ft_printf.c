/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ft_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 10:36:10 by aamorin-          #+#    #+#             */
/*   Updated: 2021/06/27 12:27:47 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char	*check_width(char *width)
{
	char	*full_flags;

	if (*flag == '-' || *flag == '+' || *flag == ' '
		|| *flag == '#' || *flag == '0')
	{
		full_flags = flag;
		flag++;
	}
	full_flags += check_width(flag);
	return (NULL);
}

char	*check_flag(char *flag)
{
	char	*full_flags;

	if (*flag == '-' || *flag == '+' || *flag == ' '
		|| *flag == '#' || *flag == '0')
	{
		full_flags = flag;
		flag++;
		full_flags += check_width(flag);
		return (full_flags);
	}
	return (NULL);
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
			flag = check_flag(nargs + 1);
			item_count++;
			if (flag != NULL)
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
	ft_printf("hola%-s", str);
	return (0);
}
