#include "philo.h"

int dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if(*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
return(0);
}

void *routine(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	if(philo->id % 2 == 0)
		ft_usleep(1);
	while(!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (p);
}

int crt_thrd(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	ob;
	int		i;

	if(pthread_create(&ob, NULL, &monitor, program->philos))
			destroy_all("thread creation error", program, forks);
	
	i = 0;
	while(i <program->philos[0].nm_philos)
	{
		if(pthread_create(&program->philos[i].thread, NULL, &routine,
					&program->philos[i])!=0)
			destroy_all("thread creation error", program, forks);
		i++;
	}
	i = 0;
	if(pthread_join(ob,NULL) != 0)
		destroy_all("thread join error", program, forks);
	while(i < program->philos[0].nm_philos)
	{
		if(pthread_join(program->philos[i].thread, NULL) != 0)
			destroy_all("thread join error", program, forks);
		i++;
	}
	return (0);
}

