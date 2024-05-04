/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:07:43 by aproust           #+#    #+#             */
/*   Updated: 2023/05/08 18:21:54 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_path(t_struct_cmd *struct_cmd, char *av)
{
	int		i;
	char	*str;

	i = -1;
	str = NULL;
	if (struct_cmd->data->path)
	{
		while (struct_cmd->data->path[++i])
		{
			str = ft_strjoin("/", struct_cmd->args[0]);
			if (!str)
				print_error(struct_cmd->data, CMD_ERR, 1);
			struct_cmd->cmd[i] = ft_strjoin(struct_cmd->data->path[i], str);
			if (!struct_cmd->cmd[i])
				print_error(struct_cmd->data, CMD_ERR, 1);
			free(str);
		}
		return ;
	}
	struct_cmd->cmd = ft_calloc(sizeof(char *), 2);
	if (struct_cmd-> cmd == NULL)
		print_error(struct_cmd->data, MALLOC_ERR, 1);
	struct_cmd->cmd[0] = ft_strjoin("/", av);
	if (struct_cmd->cmd[0] == NULL)
		print_error(struct_cmd->data, MALLOC_ERR, 1);
}

void	init_cmd(t_data *data, char **av)
{
	int	i;
	int	j;

	i = -1;
	j = 2;
	while (data->struct_cmd[++i])
	{
		data->struct_cmd[i]->args = ft_split(av[j], ' ');
		if (data->struct_cmd[i]->args == NULL)
			print_error(data, NULL, 1);
		if (ft_strchr(data->struct_cmd[i]->args[0], '/'))
			data->struct_cmd[i]->abs_path = av[j];
		else
			set_path(data->struct_cmd[i], data->struct_cmd[i]->args[0]);
		j++;
	}
}

void	alloc_struct(t_data *data, int len)
{
	int	i;

	i = -1;
	data->struct_cmd = ft_calloc(sizeof(t_struct_cmd *), 3);
	if (!data->struct_cmd)
		print_error(data, MALLOC_ERR, 1);
	while (++i < 2)
	{
		data->struct_cmd[i] = ft_calloc(sizeof(t_struct_cmd), 1);
		if (data->struct_cmd[i] == NULL)
			print_error(data, MALLOC_ERR, 1);
		if (len != 0)
		{
			data->struct_cmd[i]->cmd = ft_calloc(sizeof(char *), len + 1);
			if (data->struct_cmd[i]->cmd == NULL)
				print_error(data, MALLOC_ERR, 1);
		}
		data->struct_cmd[i]->data = data;
	}
}

void	init_struct(t_data *data, char **envp, char **av)
{
	int	i;
	int	len;

	i = -1;
	if (envp)
	{
		while (envp[++i] && ft_strnstr(envp[i], "PATH", 4) == 0)
			;
		if (envp[i])
			data->path = ft_split(&envp[i][5], ':');
	}
	len = lentab(data->path);
	alloc_struct(data, len);
	init_cmd(data, av);
}
