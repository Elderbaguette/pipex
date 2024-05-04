/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:05:19 by aproust           #+#    #+#             */
/*   Updated: 2023/05/08 15:55:04 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_all(t_data *data, int code_exit)
{
	free_tab(data->path);
	free_cmd(data->struct_cmd);
	exit(code_exit);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac >= 5)
	{
		data.path = NULL;
		data.limiter = NULL;
		data.infile = av[1];
		data.outfile = av[ac - 1];
		data.here_doc = (ft_strcmp("here_doc", av[1]) == 0);
		data.nb_cmd = ac - 3 - (data.here_doc == 1);
		data.prev_pipes = -1;
		data.envp = envp;
		init_struct(&data, envp, av);
		execute_cmd(&data);
		free_all(&data, 0);
	}
	else
		ft_printf("Not enough arguments required\n");
}
