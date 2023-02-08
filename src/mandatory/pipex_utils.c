#include "../inc/pipex.h"

/*find command path inside environment, then split and test each path
and return the correct one
if whole path, /xxx/yyy/zzz:/aaa/bbb:/ccc
first split it by : so /aaa/bbb is one location and /ccc is another
then join a / to /xxx/yyy/zzz so its /xxx/yyy/zzz/
then join the cmd for example "echo" so its /xxx/yyy/zzz/echo
if not exist the /aaa/bbb/echo , if not then /ccc/echo*/
char	*find_path(char *cmd, char **envp)
{
	char	**array_of_paths;
	char	*cmd_path;
	char	*part_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	array_of_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (array_of_paths[i])
	{
		part_path = ft_strjoin(array_of_paths[i], "/");
		cmd_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	i = -1;
	while (array_of_paths[++i])
		free(array_of_paths[i]);
	free(array_of_paths);
	return (0);
}

/*find the command path, process ends when execve is executed
path = find_path() - get the cmd path frm find path function
void	execute_cmd(char *argv, char **envp)*/
void	execute_cmd(char *argv, char **envp)
{
	char	**cmd;
	//int		i;
	char	*path;

	//i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
		perror("Error");
	if (execve(path, cmd, envp) == -1)
		perror("Error");
	execve(path, cmd, envp);
}