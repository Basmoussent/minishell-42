#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/libft.h"

enum {
	KO = 1,
	OK = 0
} ;



// Builtins

int		echo(char *str, char *params);
int		handle_echo(char *str);
int		ft_pwd(char **envp);
int		ft_env(char **envp);
void	ft_exit(void);

#endif
