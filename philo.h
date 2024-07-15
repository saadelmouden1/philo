#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PH 200

typedef struct s_philo
{
	pthread_t	thread;
	int		id;
	int		n_mls_etn;
	int 		eating;
	size_t		lst_ml;
	size_t		time_for_die;
	size_t		time_for_sleep;
	size_t		time_for_eat;
	size_t		time_strt;
	int		nm_philos;
	int		nm_time_for_eat;
	int		*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;

}	t_philo;

typedef struct	s_program
{
	int	f_dead;
	pthread_mutex_t dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}		t_program;

void inpt_initialize(t_philo *philo, char **argv);
void philos_initialize(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		                char **argv);
void    forks_initialize(pthread_mutex_t *forks, int nm_philos);
void    program_initialize(t_program *program, t_philo *philos);
int ft_strlen(char *str);
int     ft_atoi(char *str);
void destroy_all(char *str, t_program *program,pthread_mutex_t *forks);
size_t get_current_time(void);
int     ft_usleep(size_t mls);
int dead_loop(t_philo *philo);
void *routine(void *p);
int crt_thrd(t_program *program, pthread_mutex_t *forks);
void think(t_philo *philo);
void dream(t_philo *philo);
void eat(t_philo *philo);
void print_message(char *str, t_philo *philo, int id);
int     phile_dead(t_philo *philo, size_t time_for_die);
int check_if_dead(t_philo *philos);
int check_if_all_ate(t_philo *philos);
//t check_if_all_ate(t_philo *philos);
void *monitor(void *p);

#endif
