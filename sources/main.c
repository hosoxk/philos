#include "../philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		init_data(&table);
		//3) simulation
		dinner_start(&table);
		//4) no leaks -> philos full || 1 philo died
	//	clean(&table);
	}
	else
		error_exit(BOLD_GREEN"Correct usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> (<number_of_times_each_philosopher_should_eat>)\n"RESET);
	return (0);
}
