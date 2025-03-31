/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:40:03 by schiper           #+#    #+#             */
/*   Updated: 2025/03/31 14:15:53 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_validator.h"

int	main(int argc, char **argv)
{
	check_args(argc, argv);
	return (execute(init_data(argc, argv)));
}
