/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 09:58:12 by frankgar          #+#    #+#             */
/*   Updated: 2024/03/17 20:14:56 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include "libft.h"

# define E_MALLOC "Error, Malloc's fault.\n"
# define E_ENV "Error, No enviroment.\n"
# define E_NOPATH "Error, No PATH in enviorment.\n"
# define E_OPEN "Error, Not Able to Open the File.\n"
# define E_W_KO "Error, No Perms to Write.\n"
# define E_R_KO "Error, No Perms to Read.\n"
# define E_F_KO "Error, Unexistant File.\n"

typedef struct s_cmd
{
	char	*path;
	char	**cmd;
}	t_cmd;

typedef struct s_pipex
{
	t_cmd	cmd[2];
	char	*inp;
	char	*out;
	int		fd_ch1[2];
	int		fd_ch2[2];
	int		stt_c1;
	int		stt_c2;
	int		fd_inp;
	int		fd_out;
}	t_pipex;

int	basic_parsing(int argc, char **argv, t_pipex *data);
int	cmd_parsing(char **argv, char **env, t_pipex *data);

#endif
