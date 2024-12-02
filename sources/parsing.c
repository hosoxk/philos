#include "../philo.h"

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c ==32);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static const char	*valid_input(const char *str)
{
	int		length;
	const char	*nbr;

	length = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Enter only positive values");
	if (!ft_isdigit(*str))
		error_exit("The input is not a correct digit");
	nbr = str;
	while (ft_isdigit(*str++))
		length++;
	if (length > 10)
		error_exit("The value is too big, INT_MAX is the limit");
	return (nbr);
}

static long	ft_atol(const char *str)
{
	long	nbr;

	nbr = 0;
	str = valid_input(str);
	while (ft_isdigit(*str))
		nbr = (nbr * 10) + (*str++ - 48);
	if (nbr > INT_MAX)
		error_exit("The value is too big, INT_MAX is the limit");
	return (nbr);
}

void	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	if (table->philo_nbr > 200)
		error_exit("Test with no more than 200 philosophers");
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("Use timestamps major than 60ms");
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
}
