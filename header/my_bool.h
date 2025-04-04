/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_bool.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:52:22 by schiper           #+#    #+#             */
/*   Updated: 2025/04/04 15:22:48 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MY_BOOL_H)
# define MY_BOOL_H

typedef enum e_bool
{
	my_true = 1,
	my_false = 0,
}		t_bool;

t_bool	get_dead(void);
void	set_dead(t_bool my_bool);

#endif // MY_BOOL_H
