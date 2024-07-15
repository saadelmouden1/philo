#include "philo.h"

int arguments_checking(char *arg)
{
	int	i;

	i = 0;
	while(arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int validation_arg(char **argv)
{
	if(ft_atoi(argv[1]) > MAX_PH || ft_atoi(argv[1]) <= 0 || arguments_checking(argv[1]) == 1)
			return (write(2, "Invalide numbers\n" , 17), 1);
	if(ft_atoi(argv[2]) <= 0 || arguments_checking(argv[2]) == 1)
		return (write(2, "Invalide dying time\n", 21),1);
	if(ft_atoi(argv[3]) <= 0 || arguments_checking(argv[3]) == 1)
		 return (write(2, "Invalide eating time\n", 21),1);
	 if(ft_atoi(argv[4]) <= 0 || arguments_checking(argv[4]) == 1)
		return (write(2, "Invalide sleep time\n", 20),1);
	if(argv[5] && (ft_atoi(argv[5]) <= 0 || arguments_checking(argv[5]) == 1))
		return (write(2, "Invalide number of times each philosopher must eat\n",
				51), 1);
		return (0);
}

int main(int argc, char **argv)
{
	t_program	program;
	t_philo		philos[MAX_PH];
	pthread_mutex_t	forks[MAX_PH];

	if( argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if(validation_arg(argv) == 1)
		return (1);
	
	program_initialize(&program, philos);
	forks_initialize(forks, ft_atoi(argv[1]));
	philos_initialize(philos, &program, forks, argv);
	crt_thrd(&program, forks);
	destroy_all(NULL, &program, forks);
	return (0);
}
