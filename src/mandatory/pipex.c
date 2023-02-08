#include "../inc/pipex.h"

/*infile to read end of pipe
infile = open for read only
1st dup2 - pass in fd[1] to stdout, f1 is execve input
2nd dup2 - infile is execve output
close when not using (if we close fd[1] because have 2 fd
that point to the same pipe (1 original 1 copy, we duplicated it))
execute_cmd infile cmd1(argv[2]) cmd2 outfile*/
void	child_process(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, S_IRWXU);
	if (infile == -1)
		perror("Error");
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	execute_cmd(argv[2], envp);
}

/*from write end of pipe to outfile
outfile = open for write,create if not exist,truncate if exist
execute_cmd outfile cmd1 cmd2(argv[3] outfile)*/
void	parent_process(char **argv, char **envp, int *fd)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (outfile == -1)
		perror("Error");
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	execute_cmd(argv[3], envp);
}

// int fd[2] - array of 2 file descriptors (fd1 write end, fd0 read end)
// pid_t - means pid number
// (argc == 5) means 5 elements ./pipex infile cmd1 cmd2 outfile 
// pid1 = fork()- create processes 
// (pid 1 == 0) - to check if we're in child process,
//	if yes then run the child process part
// after executing child process, come back out as
// the other stuff are executed by the parent
// waitpid - wait until child process ends then execute
// the parent process. NULL-status 0-option
int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			perror("Error");
		pid1 = fork();
		if (pid1 == -1)
			perror("Error");
		if (pid1 == 0)
			child_process(argv, envp, fd);
		waitpid(pid1, NULL, 0);
		parent_process (argv, envp, fd);
	}
	else
	{
		ft_putstr_fd("Bad arguments", 2);
	}
	return (0);
}
