#include <stdio.h>
#include <limits.h>

#define ERR -1

typedef struct s_state {
	long long	n_philos;
	long long	t_die;
	long long	t_eat;
	long long	t_sleep;
	long long	n_eats;
}	t_state;

typedef struct s_philosopher {
	
}	t_philo;

long long	atoll(char *original)
{
	char		*str;
	long long	n;
	int			digit;

	str = original;
	n = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
		return (printf("Err: Negative arg: %s\n", original), ERR);
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str++ - '0';
		if (n > (LLONG_MAX - digit) / 10)
			return (printf("Err: Atoll overflow: %s\n", original), ERR);
		n = n * 10 + digit;
	}
	if (*str)
		return (printf("Err: Arg with invalid chars: %s\n", original), ERR);
	return (n);
}

int	init_state(int argc, char **argv, t_state *s)
{
	char *err = "Usage: %s n_philo, t_die, t_eat, t_sleep, [opt:n_eats]";

	if (argc != 5 && argc != 6)
		return (printf(err, argv[0]), 0);
	s->n_philos = atoll(argv[1]);
	s->t_die = atoll(argv[2]);
	s->t_eat = atoll(argv[3]);
	s->t_sleep = atoll(argv[4]);
	if (argc == 6)
		s->n_eats = atoll(argv[5]);
	if (s->n_philos <= 0 || s->t_eat <= 0 || s->t_die <= 0 || s->t_sleep <= 0 || s->n_eats < 0)
		return (printf("Err: arg '0' or not pos long long\n"), ERR);
	return (1);
}
/* number_of_philosophers time_to_die time_to_eat
 * time_to_sleep, [number_of_times_each_philosopher_must_eat]`
 */
int	main(int argc, char **argv)
{
	t_state	s;

	init_state(argc, argv, &s);
}
