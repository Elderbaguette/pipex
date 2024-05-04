/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aproust <aproust@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:05:02 by aproust           #+#    #+#             */
/*   Updated: 2023/05/09 14:24:40 by aproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libftprintfgnl/libftprintfgnl.h"

# define MALLOC_ERR "Error: while trying to malloc"
# define FORK_ERR "Error: fork failed"
# define PIPE_ERR "Error: pipe failed"
# define CMD_ERR "Error: command not found"

typedef struct data	t_data;

typedef struct t_struct_cmd
{
	char	**cmd;
	char	**args;
	char	*abs_path;
	pid_t	pid;
	t_data	*data;
}	t_struct_cmd;

typedef struct data
{
	char			**path;
	char			*infile;
	char			*outfile;
	int				nb_cmd;
	int				prev_pipes;
	int				here_doc;
	char			*limiter;
	int				here_doc_fd;
	int				fd[2];
	char			**envp;
	t_struct_cmd	**struct_cmd;
}	t_data;

int		process(int n, char **path, char **av, char **envp);
void	print_path(char *str);
int		start_process(t_data *data, char **av, char **envp, int i);
int		process(int n, char **path, char **av, char **envp);
void	init_struct(t_data *data, char **envp, char **av);
void	print_error(t_data *data, char *err_msg, int error_code);
void	free_all(t_data *data, int code_exit);
void	execute_cmd(t_data *data);
void	execute(t_struct_cmd *struct_cmd);
void	when_here_doc(t_struct_cmd *struct_cmd, int fd);
void	if_here_doc(t_struct_cmd *struct_cmd, int *fd);
void	free_cmd(t_struct_cmd **struct_cmd);

#endif
