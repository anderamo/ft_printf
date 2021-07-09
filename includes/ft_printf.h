/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamorin- <aamorin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:51:10 by aamorin-          #+#    #+#             */
/*   Updated: 2021/07/08 16:23:48 by aamorin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <stdarg.h>

typedef struct s_flags
{
	int		dot;
	int		minus;
	int		zero;
	int		plus;
	char	type;
	int		numbers;
}	t_flags;

int	ft_printf(const char *nargs, ...);

#endif

