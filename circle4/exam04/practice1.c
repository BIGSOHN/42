#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void exe(char **cmd, int flag, int count, char **envp);
void	cd_exe(char **cmd, int count);
int ft_strncmp(char *s1, char *s2, int n);
char	*ft_strdup(char *s);
void	ft_free(char **cmd);

int main(int ac, char **av, char **envp) {
	int start = 1;
	int	i;
	int count;
	int end;
	int flag;
	char **cmd;

	cmd = NULL;
	while (av[start] != NULL) {
		end = start;
		flag = 0;
		while (av[end] != NULL && ft_strncmp(av[end], "|", 2) != 0 
		&& ft_strncmp(av[end], ";", 2) != 0) {
			end++;
		}
		if (end != start) {
			if (av[end] != NULL && ft_strncmp(av[end], "|", 2) == 0)
				flag = 1;
			cmd = (char **)malloc(sizeof(char *) * (end - start + 1));
			if (cmd == NULL)
				return (0);
			i = start;
			count = 0;
			while (i < end) {
				cmd[count] = ft_strdup(av[i]);
				i++;
				count++;
			}
			cmd[count] = NULL;
			exe(cmd, flag, count, envp);
			ft_free(cmd);
			cmd = NULL;
		}
		start = end;
		if (av[end] != NULL)
			start++;
	}
	return (0);
}

void	ft_free(char **cmd) {
	int i = 0;

	while (cmd[i] != NULL)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void exe(char **cmd, int flag, int count, char **envp) {
	int fd[2];
	int pid;

	if (flag == 1) {
		pipe(fd);
	}
	if (ft_strncmp(cmd[0], "cd", 3) == 0) {
		cd_exe(cmd, count);
		if (flag == 1) {
			close(fd[0]);
			close(fd[1]);
		}
		return ;
	}
	pid = fork();
	if (pid == 0) {
		if (flag == 1) {
			dup2(fd[1], 1);
			close (fd[0]);
			close(fd[1]);
		}
		execve(cmd[0], cmd, envp);
		exit(1);
	}
	else {
		waitpid(pid, NULL, 0);
		if (flag == 1) {
			dup2(fd[0], 0);
			close (fd[0]);
			close(fd[1]);
		}
	}
}

void	cd_exe(char **cmd, int count) {
	if (count != 2) {
		return ;
	}
	printf("%s\n", cmd[1]);
	if (chdir(cmd[1]) == -1) {
		return ;
	}
}

int ft_strncmp(char *s1, char *s2, int n) {
	int	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0')) {
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
		else
			i++;
	}
	return (0);
}

char	*ft_strdup(char *s) {
	int length;
	char *dest;

	length = 0;
	while(s[length] != '\0')
		length++;
	dest = (char *)malloc(sizeof(char) * (length + 1));
	if (dest == NULL)
		return (0);
	length = 0;
	while (s[length] != '\0') {
		dest[length] = s[length];
		length++;
	}
	dest[length] = '\0';
	return (dest);
}