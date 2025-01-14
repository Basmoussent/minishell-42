void	free_args(char **envp)
{
	int i = 0;
	char **test_variable = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

