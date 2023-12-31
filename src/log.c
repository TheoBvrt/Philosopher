/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouvera <tbouvera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:52:11 by tbouvera          #+#    #+#             */
/*   Updated: 2023/10/17 11:15:37 by tbouvera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>

int	monitor_utils(t_philosopher *philo, t_table *table)
{
	if (philo->died)
	{
		die_log(table);
		return (0);
	}
	if (table->max_eat != -1 && philo->meals_eaten >= table->max_eat)
	{
		pthread_mutex_lock(&table->end_mutex);
		table->philo_done++;
		if (table->philo_done >= table->n_p)
			return (0);
		pthread_mutex_unlock(&table->end_mutex);
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	return ((long long)(ct.tv_sec * 1000 + ct.tv_usec / 1000));
}

long long	get_time_since_start(t_table *table)
{
	return (get_time() - table->start_time);
}

void	log_action(t_philosopher *ph, const char *action, t_table *table)
{
	long long	timestamp;

	if (table->stop == 1 && ph->died == 0)
		return ;
	pthread_mutex_lock(&table->log_mutex);
	if (table->stop == 1 && ph->died == 0)
	{
		pthread_mutex_unlock(&table->log_mutex);
		return ;
	}
	timestamp = get_time_since_start(table);
	printf("%lldms %d %s\n", timestamp, ph->id, action);
	pthread_mutex_unlock(&table->log_mutex);
}
