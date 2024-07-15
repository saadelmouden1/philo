#include "philo.h"

int ft_strlen(char *str)
{
	int	i;

	if(str == NULL)
		return (0);

	i = 0;
	while(str[i] != '\0')
		i++;
	return (i);
}


int	ft_atoi(char *str)
{
	unsigned long long	nbr;
	int	s;
	int	i;

	nbr = 0;
	s = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if(str[i] == '-')
		s = -1;
	if(str[i] == '-' || str[i] == '+')
		i++;
	while(str[i] >= '0' && str[i] < '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (s * nbr);

}

void destroy_all(char *str, t_program *program,  pthread_mutex_t *forks)
{
	int i;

	i = 0;
	if(str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->write_lock);
	 pthread_mutex_destroy(&program->meal_lock);  
	  pthread_mutex_destroy(&program->dead_lock);
	while(i < program->nm_philos)
	  {
		  pthread_mutex_destroy(&forks[i]);
		  i++;
	  }	
}

int	ft_usleep(size_t mls)
{
	size_t s;

	s = get_current_time();
	while((get_current_time() - s) < mls)
		usleep(500);
	return (0);
}

size_t get_current_time(void)
{
	struct timeval time;

	if(gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);

}
