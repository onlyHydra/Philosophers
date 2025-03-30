/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_limit_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:22:30 by schiper           #+#    #+#             */
/*   Updated: 2025/03/30 15:49:45 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_validator.h"
#include "my_bool.h"

static t_bool	compare_int(char *argv, void *limit)
{
	if (ft_atoi(argv) > *(int *)limit)
		return (my_false);
	return (my_true);
}

static t_bool	compare_float(char *argv, void *limit)
{
	if (ft_atof(argv) > *(float *)limit)
		return (my_false);
	return (my_true);
}

static t_bool	compare_double(char *argv, void *limit)
{
	if (ft_atod(argv) > *(double *)limit)
		return (my_false);
	return (my_true);
}

static t_bool	compare_long_long(char *argv, void *limit)
{
	if (ft_atol(argv) > *(long long *)limit)
		return (my_false);
	return (my_true);
}

t_bool	check_limit_arg(char *argv, void *limit)
{
	if (sizeof(limit) == sizeof(int))
		return (compare_int(argv, limit));
	if (sizeof(limit) == sizeof(float))
		return (compare_float(argv, limit));
	if (sizeof(limit) == sizeof(int))
		return (compare_double(argv, limit));
	if (sizeof(limit) == sizeof(int))
		return (compare_long(argv, limit));
	if (sizeof(limit) == sizeof(int))
		return (compare_long_long(argv, limit));
	return (my_false);
}
