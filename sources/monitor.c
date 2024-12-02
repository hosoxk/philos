/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:16:01 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/12/02 15:44:39 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

		if (get_bool(&philo->philo_mutex, &philo->full))
			return (false);
		elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
		t_to_die = philo->table->time_to_die / 1e3;
		if (elapsed > t_to_die)
			return (true);
		return (false);
}

void	*monitor_dinner(void *data)
{
	t_table	*table;
	int	i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, &table->threads_running_nbr, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
