/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:13:58 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/12/11 18:16:14 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		init_data(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
		error_exit(BOLD_GREEN"Correct usage: ./philo <number_of_philosophers>"
			" <time_to_die> <time_to_eat> <time_to_sleep>"
			" (<number_of_times_each_philosopher_should_eat>)\n"RESET);
	return (0);
}
