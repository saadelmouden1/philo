#include "philo.h"

void inpt_initialize(t_program *program, char **argv)
{
	if(argv[5])
		program->nm_time_for_eat = ft_atoi(argv[5]);
	else
		program->nm_time_for_eat = -1;
	program->nm_philos = ft_atoi(argv[1]);
	program->time_for_die = ft_atoi(argv[2]);
	program->time_for_eat = ft_atoi(argv[3]);
	program->time_for_sleep = ft_atoi(argv[4]);
	program->time_strt = get_current_time();
}

void philos_initialize(t_program *program,char **argv)
{
	int	i;
	i = 0;
	inpt_initialize(program, argv);

	while(i < ft_atoi(argv[1]))
	{
		program->philos[i].table = program;
		program->philos[i].id = i + 1;
		program->philos[i].eating = 0;
		program->philos[i].n_mls_etn = 0;
		//inpt_initialize(&philos[i], argv);
		//philos[i].time_strt = get_current_time();
		program->philos[i].lst_ml = get_current_time();
		//philos[i].write_lock = &program->write_lock;
		//philos[i].dead_lock = &program->dead_lock;
		//philos[i].meal_lock = &program->meal_lock;
		program->philos[i].l_fork = &program->forks[i];
		//program->f_dead = &program->f_dead;
		if(i == 0)
			program->philos[i].r_fork = &program->forks[program->nm_philos - 1];
		else
			program->philos[i].r_fork = &program->forks[i - 1];
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

void	program_initialize(t_program *program)
{
	program->f_dead = 0;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);

}

