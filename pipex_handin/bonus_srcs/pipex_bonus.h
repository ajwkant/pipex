/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akant <akant@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 12:49:55 by akant         #+#    #+#                 */
/*   Updated: 2021/12/01 17:54:33 by akant         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include <fcntl.h>

// Pipex_bonus
int		main(int argc, char **argv, char **envp);
int		pipex(int *fd, char **argv, int argc, char **envp);
void	first_child(int fd, char *cmd, int *pip, char **envp);
void	middle_child(char *cmd, int *pip, int read_end, char **envp);
void	last_child(int fd, char *cmd, int read_end, char **envp);

// Parse and helperfunctions
char	**strip_command(char *str);
char	**split_after_first_word(char *str, char c);
void	*return_null_and_free(char **split);
int		count_words(char *s, char c);
void	remove_argument_quotes(char **argv);

// Path access
char	*find_path_line(char **envp);
char	**find_paths(char **envp);
char	*check_access(char **paths, char *cmd);

// Error
int		error_return(char *str);

#endif
