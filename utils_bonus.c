/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:05:12 by aproust           #+#    #+#             */
/*   Updated: 2023/05/09 14:20:49 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	if_here_doc(t_struct_cmd *struct_cmd, int *fd)
{
	if (pipe(fd) == -1)
		print_error(struct_cmd->data, NULL, 1);
	when_here_doc(struct_cmd, fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	execute(t_struct_cmd *struct_cmd)
{
	int		i;
	char	*ev[2];

	ev[0] = "TERM=xterm";
	ev[1] = NULL;
	i = -1;
	while (struct_cmd->cmd[++i])
	{
		if (ft_strncmp(struct_cmd->args[0], "top", 3) == 0)
			execve(struct_cmd->cmd[i], struct_cmd->args, (char *const *)ev);
		if (access(struct_cmd->cmd[i], X_OK) == 0)
			execve(struct_cmd->cmd[i], struct_cmd->args, NULL);
	}
	if (struct_cmd->abs_path && access(struct_cmd->abs_path, F_OK) == 0)
		execve(struct_cmd->abs_path, struct_cmd->args, NULL);
	print_error(struct_cmd->data, CMD_ERR, 1);
}

void	when_here_doc(t_struct_cmd *struct_cmd, int fd)
{
	char	*buffer;
	char	*str;

	str = ft_strjoin(struct_cmd->data->limiter, "\n");
	if (!str)
		print_error(struct_cmd->data, NULL, 1);
	buffer = get_next_line(0);
	if (ft_strcmp(buffer, str) == 0)
		return (free(str), free(buffer));
	if (write(fd, buffer, ft_strlen(buffer)) == -1)
		return (free(str), free(buffer));
	while (ft_strcmp(buffer, str) != 0)
	{
		free(buffer);
		buffer = get_next_line(0);
		if (write(fd, buffer, ft_strlen(buffer)) == -1)
			return (free(str));
	}
	free(str);
	close(fd);
}
