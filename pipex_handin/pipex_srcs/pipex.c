/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 14:37:28 by akant         #+#    #+#                 */
/*   Updated: 2021/12/01 18:49:14 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int fd, char *cmd, int *pip, char **envp)
{
	char	**paths;
	char	*working_path;
	char	**split;

	split = strip_command(cmd);
	if (split == NULL)
		exit(EXIT_FAILURE);
	close(pip[0]);
	dup2(pip[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(pip[1]);
	close(fd);
	paths = find_paths(envp);
	working_path = check_access(paths, split[0]);
	ft_split_free(paths);
	if (!working_path)
	{
		perror("First command not found\n");
		exit(127);
	}
	execve(working_path, split, envp);
	perror("Error na execve in first child.\n");
	exit(EXIT_FAILURE);
}

void	last_child(int fd, char *cmd, int *pip, char **envp)
{
	char	**paths;
	char	*working_path;
	char	**split;

	split = strip_command(cmd);
	if (split == NULL)
		exit(EXIT_FAILURE);
	close(pip[1]);
	dup2(pip[0], STDIN_FILENO);
	close(pip[0]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	paths = find_paths(envp);
	working_path = check_access(paths, split[0]);
	ft_split_free(paths);
	if (!working_path)
	{
		perror("Second command not found\n");
		exit(127);
	}
	execve(working_path, split, envp);
	perror("Error na execve in last child.\n");
	exit(EXIT_FAILURE);
}

void	wait_function(int status, pid_t child1, pid_t child2)
{
	waitpid(child1, &status, 0);
	if (!WIFEXITED(status))
		exit(EXIT_FAILURE);
	waitpid(child2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

int	pipex(int *fd char **argv, int argc, char **envp)
{
	int		pip[2];
	pid_t	child1;
	pid_t	child2;
	int		status;

	if (pipe(pip) == -1)
		return (error_return("Pipe: \n"));
	child1 = fork();
	if (child1 < 0)
		return (error_return("Forking: \n"));
	if (child1 == 0)
		first_child(fd[0], argv[2], pip, envp);
	close(pip[1]);
	child2 = fork();
	if (child2 < 0)
		return (error_return("Forking: \n"));
	if (child2 == 0)
		last_child(fd[1], argv[3], pip, envp);
	close(pip[1]);
	wait_function(status, child1, child2);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	return_value;
	int	fd[2];

	if (argc < 5)
		return (error_return("Error: A minimal of 5 arguments needed.\n"));
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
		return (error_return("Error: opening inputfile failed.\n"));
	fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT, 00644);
	if (fd[1] == -1)
		return (error_return("Error: opening outputfile failed.\n"));
	returnvalue = pipex(fd, argv, argc, envp));
	while (wait(0) != -1)
		;
	return (return_value);
}
