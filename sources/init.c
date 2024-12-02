/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:14:28 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/12/02 15:27:33 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	if (philo->id % 2)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
	else
	{
		philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
		philo->second_fork = &forks[philo_position];
	}
	/*printf("philo[%d] first fork: %d\n", philo->id, philo->first_fork->fork_id);
	printf("philo[%d] second fork: %d\n", philo->id, philo->second_fork->fork_id);*/
}

static void	init_philo(t_table *table)
{
	int	i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
	/*i = -1;
	while (++i < table->philo_nbr)
	{
		printf("philo id: %d\n", table->philos[i].id);
	}*/
}

void	init_data(t_table *table)
{
	int	i;

	i = -1;
	table->all_threads_ready = false;
	table->end_simulation = false;
	table->threads_running_nbr = 0;
	table->philos = safe_malloc(sizeof (t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof (t_fork) * table->philo_nbr);
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_mutex, INIT);
	while (++i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	init_philo(table);
}
