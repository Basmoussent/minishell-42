void	free_args(char **envp)
{
	int i;

	char **test_variable;

	test_variable = ft_split(envp, '=');
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

