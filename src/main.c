/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:44:08 by frankgar          #+#    #+#             */
/*   Updated: 2024/03/22 11:17:52 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	child_two(int fork, t_pipex *data, char **env)
{
	if (fork == -1)
	{
		perror("Pipex: ");
		exit(1);
	}
	if (data->stt_c2 < 0)
		exit(1);
	if (dup2(data->fd_ch1[0], 0) == -1)
	{
		perror("Pipex: ");
		exit(1);
	}
	close(data->fd_ch1[0]);
	close(data->fd_ch1[1]);
	if (dup2(data->fd_out, 1) == -1)
	{
		perror("Pipex: ");
		exit(1);
	}
	close(data->fd_inp);
	close(data->fd_out);
	execve(data->cmd[1].path, data->cmd[1].cmd, env);
	exit(ft_fd_printf(2, "Pipex: [%s] Command not found\n", \
				data->cmd[1].cmd[0]) * 0 + 127);
}

int	child_one(int fork, t_pipex *data, char **env)
{
	if (fork == -1)
	{
		perror("Pipex: ");
		exit(1);
	}
	if (data->stt_c1 < 0)
		exit(1);
	if (dup2(data->fd_ch1[1], 1) == -1)
	{
		perror("Pipex: ");
		exit(1);
	}
	close(data->fd_ch1[0]);
	close(data->fd_ch1[1]);
	if (dup2(data->fd_inp, 0) == -1)
	{
		perror("Pipex: ");
		exit(1);
	}
	close(data->fd_inp);
	close(data->fd_out);
	execve(data->cmd[0].path, data->cmd[0].cmd, env);
	exit(ft_fd_printf(2, "Pipex: [%s] Command not found\n", \
				data->cmd[0].cmd[0]) * 0 + 127);
}

int	pipex(int argc, char **argv, char **env)
{
	t_pipex	data;
	int		fork1;
	int		fork2;

	ft_bzero(&data, sizeof(t_pipex));
	basic_parsing(argc, argv, &data);
	cmd_parsing(argv, env, &data);
	pipe(data.fd_ch1);
	fork1 = fork();
	if (fork1 == 0)
		child_one(fork1, &data, env);
	fork2 = fork();
	if (fork2 == 0)
		child_two(fork2, &data, env);
	close(data.fd_ch1[0]);
	close(data.fd_ch1[1]);
	close(data.fd_inp);
	close(data.fd_out);
	waitpid(fork1, &data.stt_c1, 0);
	waitpid(fork2, &data.stt_c2, 0);
	return (WEXITSTATUS(data.stt_c2));
}

int	main(int argc, char **argv, char **env)
{
	return (pipex(argc, argv, env));
}
