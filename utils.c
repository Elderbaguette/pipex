/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:05:12 by aproust           #+#    #+#             */
/*   Updated: 2023/05/09 14:20:45 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(t_data *data, char *err_msg, int error_code)
{
	if (!err_msg)
		perror("Error");
	else
		ft_putendl_fd(err_msg, 2);
	free_all(data, error_code);
}

void	free_cmd(t_struct_cmd **struct_cmd)
{
	int	i;

	i = -1;
	if (!struct_cmd)
		return ;
	while (struct_cmd[++i])
	{
		free_tab(struct_cmd[i]->args);
		free_tab(struct_cmd[i]->cmd);
		free(struct_cmd[i]);
	}
	free(struct_cmd);
}

void	free_all(t_data *data, int code_exit)
{
	free_tab(data->path);
	free_cmd(data->struct_cmd);
	exit(code_exit);
}
