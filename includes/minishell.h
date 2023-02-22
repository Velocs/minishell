/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 22:12:54 by aliburdi          #+#    #+#             */
/*   Updated: 2023/02/22 17:20:10 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>

typedef struct s_struct
{
	char	*input;
	char	**args;
	char	*dir;
	int		arg_count;
	int		status;
	int		i;
	int		start;
	int		quotes;
	pid_t	pid;
}				t_struct;

#endif