/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:55:47 by frankgar          #+#    #+#             */
/*   Updated: 2024/03/17 20:13:43 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	get_path(char **path, t_pipex *data)
{
	int		y;
	int		x;
	char	*tmp;

	y = -1;
	while (++y <= 1)
	{
		x = -1;
		while (path[++x])
		{
			tmp = ft_strjoin(path[x], data->cmd[y].cmd[0]);
			if (!tmp)
				exit(ft_fd_printf(2, "%s", E_MALLOC) * 0 + 1);
			if (access(tmp, 0) == 0)
				data->cmd[y].path = ft_strdup(tmp);
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
		}
	}
	return (0);
}

int	get_content(char **argv, t_pipex *data, char **path)
{
	char	*tmp;
	int		i;

	i = -1;
	data->cmd[0].cmd = ft_split(argv[2], ' ');
	data->cmd[1].cmd = ft_split(argv[3], ' ');
	if (!data->cmd[0].cmd || !data->cmd[1].cmd)
		exit(ft_fd_printf(2, "%s", E_MALLOC) * 0 + 1);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			exit(ft_fd_printf(2, "%s", E_MALLOC) * 0 + 1);
		else
		{
			free(path[i]);
			path[i] = ft_strdup(tmp);
			free(tmp);
			tmp = NULL;
		}
	}
	get_path(path, data);
	return (0);
}

int	cmd_parsing(char **argv, char **env, t_pipex *data)
{
	int		y;
	char	**path;

	path = NULL;
	y = -1;
	if (!env)
		exit(ft_fd_printf(2, "%s", E_ENV) * 0 + 1);
	while (env[++y] && !path)
	{
		if (!ft_strncmp(env[y], "PATH=", 5))
		{
			path = ft_split(&env[y][5], ':');
			if (!path)
				exit(ft_fd_printf(2, "%s", E_MALLOC) * 0 + 1);
		}
	}
	if (!path)
		exit(ft_fd_printf(2, "%s", E_NOPATH) * 0 + 1);
	get_content(argv, data, path);
	return (0);
}

int	basic_parsing(int argc, char **argv, t_pipex *data)
{
	if (argc != 5)
		exit(ft_fd_printf(2, "Error of Arguments\n") * 0 + 1);
	if (access(argv[1], F_OK) == -1)
		data->stt_c1 = ft_fd_printf(2, "%s: %s", argv[1], E_F_KO) * 0 - 1;
	else if (access(argv[1], R_OK) == -1)
		data->stt_c1 = ft_fd_printf(2, "%s: %s", argv[1], E_R_KO) * 0 - 1;
	if (access(argv[4], F_OK) == 0 && access(argv[4], W_OK) == -1)
		data->stt_c2 = ft_fd_printf(2, "%s: %s", argv[4], E_W_KO) * 0 - 1;
	data->fd_inp = open(argv[1], O_RDONLY);
	if (data->fd_inp < 0)
		data->stt_c1 = ft_fd_printf(2, "%s: %s", argv[1], E_OPEN) * 0 - 1;
	data->fd_out = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0666);
	if (data->fd_out < 0)
		data->stt_c2 = ft_fd_printf(2, "%s: %s", argv[4], E_OPEN) * 0 - 1;
	data->inp = ft_strdup(argv[1]);
	data->out = ft_strdup(argv[4]);
	if (!data->inp || !data->out)
		exit(ft_fd_printf(2, "%s", E_MALLOC) * 0 + 1);
	return (0);
}
