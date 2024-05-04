/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:54:36 by aproust           #+#    #+#             */
/*   Updated: 2023/05/09 14:22:27 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(t_struct_cmd *struct_cmd)
{
	int		i;
	char	*ev[2];

	ev[0] = "TERM=xterm";
	ev[1] = NULL;
	i = -1;
	while (struct_cmd->cmd[++i])
	{
		if (access(struct_cmd->cmd[i], X_OK) == 0)
		{
			if (ft_strncmp(struct_cmd->args[0], "top", 3) == 0)
				execve(struct_cmd->cmd[i], struct_cmd->args, (char *const *)ev);
			else
				execve(struct_cmd->cmd[i], struct_cmd->args, NULL);
		}
	}
	if (struct_cmd->abs_path && access(struct_cmd->abs_path, F_OK) == 0)
		execve(struct_cmd->abs_path, struct_cmd->args, NULL);
	print_error(struct_cmd->data, CMD_ERR, 1);
}

void	first_process(t_struct_cmd *struct_cmd)
{
	int	fd;

	fd = open(struct_cmd->data->infile, O_RDONLY, 0644);
	if (fd == -1)
	{
		close(struct_cmd->data->fd[1]);
		close(struct_cmd->data->fd[0]);
		print_error(struct_cmd->data, NULL, 1);
	}
	close(struct_cmd->data->fd[0]);
	dup2(fd, STDIN_FILENO);
	dup2(struct_cmd->data->fd[1], STDOUT_FILENO);
	close(struct_cmd->data->fd[1]);
	close(fd);
	execute(struct_cmd);
}

void	last_process(t_struct_cmd *struct_cmd)
{
	int	fd;

	close(struct_cmd->data->fd[1]);
	close(struct_cmd->data->fd[0]);
	fd = open(struct_cmd->data->outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		close(struct_cmd->data->prev_pipes);
		print_error(struct_cmd->data, NULL, 1);
	}
	dup2(fd, STDOUT_FILENO);
	dup2(struct_cmd->data->prev_pipes, STDIN_FILENO);
	close(struct_cmd->data->prev_pipes);
	close(fd);
	execute(struct_cmd);
}

void	start_processing(t_data *data, int i)
{
	if (i == 0)
		first_process(data->struct_cmd[i]);
	else
		last_process(data->struct_cmd[i]);
}

void	execute_cmd(t_data *data)
{
	int	i;

	i = -1;
	while (data->struct_cmd[++i])
	{
		if (pipe(data->fd) == -1)
			print_error(data, PIPE_ERR, 1);
		data->struct_cmd[i]->pid = fork();
		if (data->struct_cmd[i]->pid == -1)
			print_error(data, FORK_ERR, 1);
		if (data->struct_cmd[i]->pid == 0)
			start_processing(data, i);
		if (data->prev_pipes != -1)
			close(data->prev_pipes);
		data->prev_pipes = data->fd[0];
		close(data->fd[1]);
	}
	close(data->prev_pipes);
	i = -1;
	while (data->struct_cmd[++i])
		waitpid(data->struct_cmd[i]->pid, NULL, 0);
}
