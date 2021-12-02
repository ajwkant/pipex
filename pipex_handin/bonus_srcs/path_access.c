/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_access.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 12:09:35 by akant         #+#    #+#                 */
/*   Updated: 2021/12/01 16:37:16 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path_line(char **envp)
{
	while (ft_strncmp(*envp, "PATH=", 5))
		envp++;
	return (*envp);
}

char	**find_paths(char **envp)
{
	char	*path_start;
	char	*path_copy;
	char	**all_paths;

	path_start = find_path_line(envp);
	path_copy = ft_substr(path_start, 5, ft_strlen(path_start) - 5);
	all_paths = ft_split(path_copy, ':');
	free(path_copy);
	return (all_paths);
}

char	*check_access(char **paths, char *cmd)
{
	char	*str_slash;
	char	*str;

	str_slash = ft_strjoin(*paths, "/");
	if (!str_slash)
		return (NULL);
	str = ft_strjoin(str_slash, cmd);
	if (!str)
		return (NULL);
	free(str_slash);
	while (!(access(str, F_OK) == 0 && access(str, X_OK) == 0))
	{
		free(str);
		paths++;
		if (!*paths)
			return (NULL);
		str_slash = ft_strjoin(*paths, "/");
		if (!str_slash)
			return (NULL);
		str = ft_strjoin(str_slash, cmd);
		if (!str)
			return (NULL);
		free(str_slash);
	}
	return (str);
}
