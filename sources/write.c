/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:15:31 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/12/11 18:19:08 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	write_status_debug(t_philo_status status, t_philo *philo,
			long elapsed)
{
	if (status == TAKE_FIRST_FORK && !simulation_finished(philo->table))
		printf(BOLD_WHITE"%6ld"RESET"%d has taken the 1° fork"
			"\t\t\tn°"BOLD_BLUE"[%d]\n"RESET, elapsed, philo->id,
			philo->first_fork->fork_id);
	else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->table))
		printf(BOLD_WHITE"%6ld"RESET"%d has taken the 2° fork"
			"\t\t\tn°"BOLD_BLUE"[%d]\n"RESET, elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(BOLD_WHITE"%6ld"BOLD_CYAN"%d is eating"
			"\t\t\t"BOLD_YELLOW"[%ld]\n"RESET, elapsed, philo->id,
			philo->meals_counter);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(BOLD_WHITE"%6ld"RESET"%d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(BOLD_WHITE"%6ld"RESET"%d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf(BOLD_RED"\t\t%6ld %d died\n"RESET, elapsed, philo->id);
}

static void	print_status(t_philo_status status, t_philo *philo, long elapsed)
{
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->table))
		printf(BOLD_WHITE"%-6ld"RESET"%d has taken a fork\n",
			elapsed, philo->id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(BOLD_WHITE"%-6ld"BOLD_CYAN"%d is eating\n"RESET,
			elapsed, philo->id);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(BOLD_WHITE"%-6ld"RESET BOLD_BLUE"%d is sleeping\n"RESET,
			elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(BOLD_WHITE"%-6ld"RESET BOLD_MAGENTA"%d is thinking\n"RESET,
			elapsed, philo->id);
	else if (status == DIED)
		printf(BOLD_RED"%-6ld %d died\n"RESET, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	if (philo->full)
		return ;
	elapsed = get_time(MILLISECOND) - philo->table->start_simulation;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		print_status(status, philo, elapsed);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
