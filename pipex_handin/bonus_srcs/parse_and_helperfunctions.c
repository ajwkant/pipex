/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_and_helperfunctions.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 12:09:35 by akant         #+#    #+#                 */
/*   Updated: 2021/12/01 16:13:55 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	remove_argument_quotes(char **argv)
{
	char	*temp;

	temp = ft_strtrim(argv[1], "\'");
	free(argv[1]);
	argv[1] = temp;
}

int	count_words(char *s, char c)
{
	int	size;
	int	boolean;

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

void	*return_null_and_free(char **split)
{
	ft_split_free(split);
	return (NULL);
}

char	**split_after_first_word(char *str, char c)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != c)
		i++;
	split = malloc((3) * sizeof(char *));
	if (!split)
		return (NULL);
	split[0] = ft_substr(str, 0, i);
	if (!split[0])
		return (return_null_and_free(split));
	while (str[i + 1 + j])
		j++;
	split[1] = ft_substr(str, i + 1, j);
	if (!split[1])
		return (return_null_and_free(split));
	split[2] = NULL;
	return (split);
}

char	**strip_command(char *str)
{
	int		words;
	char	*temp;
	char	**seperated_command;

	words = count_words(str, ' ');
	if (words == 1)
		return (ft_split(str, ' '));
	else
	{
		seperated_command = split_after_first_word(str, ' ');
		if (!seperated_command)
			return (NULL);
		remove_argument_quotes(seperated_command);
		if (!seperated_command[1])
			return (NULL);
		temp = ft_strjoin(seperated_command[0], " ");
		if (!str)
			return (NULL);
		str = ft_strjoin(temp, seperated_command[1]);
		free(temp);
		if (!str)
			return (NULL);
		ft_split_free(seperated_command);
		return (ft_split(str, ' '));
	}
}
