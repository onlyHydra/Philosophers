/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validator.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:46:57 by schiper           #+#    #+#             */
/*   Updated: 2025/03/30 15:41:11 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(ARGS_VALIDATOR_H)
# define ARGS_VALIDATOR_H
# include "libft.h"
# include "my_bool.h"

char	**split_args_by(char *argv, char *splitter);
t_bool	check_limit_arg(char *argv, void *limit);

#endif // ARGS_VALIDATOR_H)
