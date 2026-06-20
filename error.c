/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   error.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: jualissa <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/06/20 19:44:31 by jualissa       #+#    #+#                */
/*   Updated: 2026/06/20 19:44:34 by jualissa       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	not_correct_number_argument(int argc)
{
	if (argc != 5 && argc != 6)
		return (1);
	return (0);
}

void	error_exit(char *error)
{
	printf("%s", error);
	exit(1);
}
