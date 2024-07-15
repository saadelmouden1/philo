#include "philo.h"

void inpt_initialize(t_philo *philo, char **argv)
{
	if(argv[5])
		philo->nm_time_for_eat = ft_atoi(argv[5]);
	else
		philo->nm_time_for_eat = -1;
	philo->nm_philos = ft_atoi(argv[1]);
	philo->time_for_die = ft_atoi(argv[2]);
	philo->time_for_eat = ft_atoi(argv[3]);
	philo->time_for_sleep = ft_atoi(argv[4]);
}

void philos_initialize(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		char **argv)
{
	int	i;
	i = 0;
	while(i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].n_mls_etn = 0;
		inpt_initialize(&philos[i], argv);
		philos[i].time_strt = get_current_time();
		philos[i].lst_ml = get_current_time();
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].l_fork = &forks[i];
		philos[i].dead = &program->f_dead;
		if(i == 0)
			philos[i].r_fork = &forks[philos[i].nm_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	forks_initialize(pthread_mutex_t *forks, int nm_philos)
{
	int	i;

	i = 0;
	while(i < nm_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	program_initialize(t_program *program, t_philo *philos)
{
	program->f_dead = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);

}

