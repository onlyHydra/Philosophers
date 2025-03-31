/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:03:54 by schiper           #+#    #+#             */
/*   Updated: 2025/03/31 17:20:54 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_threads(void)
{
}

int	execute(t_params *params)
{
	int	execution_value;

	init_threads();
	execution_value = run_threads();
	free_params(params);
	return (execution_value);
}
