/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:05:19 by aproust           #+#    #+#             */
/*   Updated: 2023/05/08 15:55:30 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac == 5)
	{
		data.path = NULL;
		data.infile = av[1];
		data.outfile = av[ac - 1];
		data.prev_pipes = -1;
		init_struct(&data, envp, av);
		execute_cmd(&data);
		free_all(&data, 0);
	}
	else
		ft_printf("Error wrong number of arguments\n");
}
