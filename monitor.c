/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-moud <sel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:43:34 by sel-moud          #+#    #+#             */
/*   Updated: 2024/10/18 14:43:36 by sel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void print_message(char *str, t_philo *philo, int id)
{
	size_t t;

	pthread_mutex_lock(philo->write_lock);
	t = get_current_time() - philo->time_strt;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", t, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	phile_dead(t_philo *philo, size_t time_for_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if(get_current_time() - philo->lst_ml >= time_for_die)
	{
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return(0);
}

int check_if_dead(t_philo *philos)
{
	int i;

	i = 0;
	while(i < philos[0].nm_philos)
	{
		if(phile_dead(&philos[i], philos[i].time_for_die))
		{
			print_message("died",&philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return 1;
		}
		i++;
	}
	return 0;
}


int check_if_all_ate(t_philo *philos)
{
    int i;
    int f_e = 0;

    if (philos[0].nm_time_for_eat == -1) // No limit on number of meals
        return 0;

    i = 0;
    while (i < philos[0].nm_philos)
    {
        pthread_mutex_lock(philos[i].meal_lock);
        if (philos[i].n_mls_etn >= philos[i].nm_time_for_eat) // Philosopher has eaten enough
            f_e++;
        pthread_mutex_unlock(philos[i].meal_lock);
        i++;
    }

    if (f_e == philos[0].nm_philos) // All philosophers have eaten enough
    {
        pthread_mutex_lock(philos[0].dead_lock);
        *philos->dead = 1;  // Signal all threads to stop
        pthread_mutex_unlock(philos[0].dead_lock);
        return 1;
    }
    return 0;
}

void *monitor(void *p)
{
	t_philo *philos;

	philos = (t_philo *)p;
	while(1)
		if(check_if_dead(philos) == 1 || check_if_all_ate(philos) ==1)
			break;
	return p;
}



