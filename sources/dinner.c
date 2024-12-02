#include "../philo.h"

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
	{
		set_bool(&philo->philo_mutex, &philo->full, true);
		printf("Philosopher %d is full\n", philo->id);
	}
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);	//spinlock --> not the best performance wise
	//set last meal time
	while (!simulation_finished(philo->table))
	{
		//1) am i full?
		if (philo->full)
			break ;
		//2) eat
		eat(philo);
		//3) sleep -> write_status & precise usleep
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		//4) think
		thinking(philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		;
	else	//create all threads
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	//*** start of simulation ***
	table->start_simulation = get_time(MILLISECOND);
	printf("Dinner starting time: %ld\n", table->start_simulation);
	//now all threads are ready!
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	//wait for everyone
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	//if we manage to reach this line, all philos are full
}
