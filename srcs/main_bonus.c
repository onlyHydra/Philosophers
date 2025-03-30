/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:16:48 by schiper           #+#    #+#             */
/*   Updated: 2025/03/30 16:23:23 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_bool.h"

int	main(int argc, char const *argv[])
{
	char	*message;

	message = "";
	if (check_argv(argc, argv) != my_false)
	{
		write(1, message, ft_strlen(message));
		return (1);
	}
	return (execution(parse_args(argc, argv)));
}
