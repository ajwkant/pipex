/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 14:37:28 by akant         #+#    #+#                 */
/*   Updated: 2021/11/04 12:12:55 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// check returnvalue check access
// Remove single quotes with strtrim

void	first_child(int fd, char *cmd, int *pip, char **envp)
{
	char	**paths;
	char	*working_path;
	char	**argv;

	argv = split_command(cmd, ' ');
	if (argv == NULL)
		return ; // --------------- error
	if (argv[1])
		remove_argument_quotes(argv);
	dup2(fd, STDIN_FILENO);
	dup2(pip[1], STDOUT_FILENO);
	close(pip[0]);
	close(fd);
	paths = find_paths(envp);
	working_path =  check_access(paths, argv[0]);
	if (!working_path)
	{
		perror("Error in check_access() in child 1.\n");
		exit(EXIT_FAILURE);
	}
	execve(working_path, argv, envp);
	perror("Error na execve in first child.\n");
	exit(EXIT_FAILURE);
}

void	second_child(int fd, char *cmd, int *pip, char **envp)
{
	char	**paths;
	char	*working_path;
	char	**argv;

	argv = split_command(cmd, ' ');
	if (argv == NULL)
		return ; // --------------- error
	if (argv[1])
		remove_argument_quotes(argv);
	close(pip[1]);
	dup2(fd, STDOUT_FILENO);
	dup2(pip[0], STDIN_FILENO);
	close(fd);
	close(pip[0]);
	paths = find_paths(envp);
	working_path = check_access(paths, argv[0]);
	if (!working_path)
	{
		perror("Error in check_access() in child 2.\n");
		exit(EXIT_FAILURE);
	}
	execve(working_path, argv, envp);
	perror("Error na execve in second child.\n");
	exit(EXIT_FAILURE);
}

int		pipex(int f1, int f2, char **argv, char **envp)
{
	int		pip[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(pip) == -1)
		return (error_return("Error: creating pipe failed.\n")); // error check after this
	child1 = fork();
	if (child1 < 0)
		return (error_return("Error: Fork"));
	if (child1 == 0)
		first_child(f1, argv[2], pip, envp);
	child2 = fork();
	if (child2 < 0)
		return (error_return("Error: Fork"));
	if (child2 == 0)
		second_child(f2, argv[3], pip, envp);
	close(pip[0]);
	close(pip[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	int fd1;
	int fd2;

	if (argc != 5)
		return (error_return("Error: 5 arguments needed.\n"));
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_WRONLY | O_CREAT, 00644);
	if (fd1 == -1)
		return (error_return("Error: opening inputfile failed.\n"));
	if (fd2 == -1)
		return (error_return("Error: opening outputfile failed.\n"));
	return (pipex(fd1, fd2, argv, envp));
}
