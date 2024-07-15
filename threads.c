#include "philo.h"

int dead_loop(t_program *program)
{
	pthread_mutex_lock(&program->dead_lock);
	if(program->f_dead == 1)
		return (pthread_mutex_unlock(&program->dead_lock), 1);
	pthread_mutex_unlock(&program->dead_lock);
return(0);
}

void *routine(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	if(philo->id % 2 == 0)
		ft_usleep(1);
	while(!dead_loop(philo->table))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (p);
}

int crt_thrd(t_program *program)
{
	pthread_t	ob;
	int		i;

	if(pthread_create(&ob, NULL, &monitor, program->philos))
			destroy_all("thread creation error", program, program->forks);
	
	i = 0;
	while(i <program->nm_philos)
	{
		if(pthread_create(&program->philos[i].thread, NULL, &routine,
					&program->philos[i])!=0)
			destroy_all("thread creation error", program, program->forks);
		i++;
	}
	i = 0;
	if(pthread_join(ob,NULL) != 0)
		destroy_all("thread join error", program, program->forks);
	while(i < program->nm_philos)
	{
		if(pthread_join(program->philos[i].thread, NULL) != 0)
			destroy_all("thread join error", program, program->forks);
		i++;
	}
	return (0);
}

