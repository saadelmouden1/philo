/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-moud <sel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:43:21 by sel-moud          #+#    #+#             */
/*   Updated: 2024/10/18 14:43:23 by sel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->time_for_sleep);
}


void eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo, philo->id);
	if(philo->nm_philos == 1)
	{
		ft_usleep(philo->time_for_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->lst_ml = get_current_time();
	philo->n_mls_etn++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_for_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
