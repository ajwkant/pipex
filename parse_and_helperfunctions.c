/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_and_helperfunctions.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 12:09:35 by akant         #+#    #+#                 */
/*   Updated: 2021/11/04 12:12:54 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		error_return(char *str)
{
	perror(str);
	return (-1);
}

void	remove_argument_quotes(char **argv)
{
	char *temp;

	temp = ft_strtrim(argv[1], "\"");
	free(argv[1]);
	argv[1] = temp;
}

int		count_words(char *s, char c)
{
	int	size;
	int boolean;

	size = 0;
	boolean = 1;
	while (*s)
	{
		if (*s != c)
		{
			if (boolean)
				size++;
			boolean = 0;
		}
		else
			boolean = 1;
		s++;
	}
	if (!size)
		return (1);
	return (size);
}

char	**split_command(char *cmd, char c)
{
	int		i;
	int		j;
	int		words;
	char	**split;

	i = 0;
	j = 0;
	words = count_words(cmd, c);
	if (!(words >= 1))
		return (NULL);
	while (cmd[i] != c)
		i++;
	split = malloc((words + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split[0] = ft_substr(cmd, 0, i);
	if (!split[0])
		return (NULL);
	if (words >= 2)
	{
		while (cmd[i + 1 + j])
			j++;
		split[1] = ft_substr(cmd, i + 1, j);
		if (!split[1])
			return (NULL);
	}
	if (words >= 2)
		split[2] = NULL;
	else
		split[1] = NULL;
	return (split);
}
