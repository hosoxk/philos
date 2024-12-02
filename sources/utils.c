#include "../philo.h"

//time_code -> SECONDS MILLISECONDS MICROSECONDS
long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to get_time");
	return (1388); //it'll never get to this line but function needs return
}

//*** precise usleep, real one sucks ***
//use table to check if simulation is finished
//1) usleep the majority of time, not CPU intensive
//2) refine last microsec with spinlock
void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2); //!!!!!!!!!!!!!!!!!!! usec / 2 ????????
		else
		{
			//SPINLOCK
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

void	error_exit(const char *error)
{
	printf(BOLD_RED"%s\n"RESET, error);
	exit(EXIT_FAILURE);
}
