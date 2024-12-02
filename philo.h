#ifndef PHILO_H
# define PHILO_H

#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> //mutex and threads
#include <sys/time.h> //gettimeofday
#include <limits.h> //INT_MAX
#include <errno.h>

//*** ANSI escape sequences for bold text colors ***
// Usage: printf(BOLD_RED "This text is bold red!" RESET "\n");

#define RESET		"\033[0m"
#define BOLD_RED	"\033[1;31m"
#define BOLD_GREEN	"\033[1;32m"
#define BOLD_YELLOW	"\033[1;33m"
#define BOLD_BLUE	"\033[1;34m"
#define BOLD_MAGENTA	"\033[1;35m"
#define BOLD_CYAN	"\033[1;36m"
#define BOLD_WHITE	"\033[1;37m"

//*** write function macro ***
#define DEBUG_MODE 1

//*** philo states ***
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

//*** OPCODE for mutex | thread functions
typedef enum	e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

//*** codes for get_time ***
typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

//*** structures ***

typedef pthread_mutex_t	t_mtx;

//IOU for compiler
typedef struct s_table	t_table;

typedef struct	s_fork
{
	t_mtx	fork;
	int	fork_id;
}	t_fork;

typedef struct s_philo
{
	int		id;
	long		meals_counter;
	bool		full;
	long		last_meal_time; //time passed from last meal
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex; //useful for races with the monitor
	t_table		*table;
}	t_philo;

typedef struct	s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	bool		end_simulation; //a philo dies or all philos are full
	bool		all_threads_ready; //synchronize philos
	long		threads_running_nbr;
	pthread_t	monitor;
	t_mtx		table_mutex; //avoid races while reading from table
	t_mtx		write_mutex;
	t_fork		*forks; //array forks
	t_philo		*philos; //array philos
}	t_table;

//*** prototypes ***

//parsing
void	parse_input(t_table *table, char **argv);

//initializing
void	init_data(t_table *table);

//utils
void	error_exit(const char *error);
long	get_time(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	wait_all_threads(t_table *table);

//safe functions
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);

//synchro utils
void	wait_all_threads(t_table *table);
void	increase_long(t_mtx *mutex, long *value);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);

//setters and getters
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	simulation_finished(t_table *table);

//write
void	write_status(t_philo_status status, t_philo *philo, bool debug);

//dinner simulation
void	dinner_start(t_table *table);
void	*lone_philo(void *arg);
void	*dinner_simulation(void *data);

//monitor
void	*monitor_dinner(void *data);

# endif
