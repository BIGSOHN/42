#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void	cd_exe(char **cmd, int count);
void	ft_exe(char **cmd, int flag, int cmd_count, char **envp);

int	ft_strncmp(char *s1, char *s2, int n) {
	int i = 0;

	while (i < n && s1[i] != '\0' && s2[i] != '\0') {
		if (s1[i] > s2[i]) {
			return (1);
		}
		else if (s1[i] < s2[i]) {
			return (-1);
		}
		i++;
	}
	return (0);
}

char	*ft_strdup (char *src) {
	int	i = 0;
	int	len = 0;
	char	*dest = NULL;

	while (src[len] != '\0')
		len++;
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (0);
	dest[len] = '\0';
	while (i < len) {
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

void ft_free(char **cmd) {
	int i = 0;
	while (cmd[i] != NULL) {
		free(cmd[i]);
		i++;
	}
	free(cmd);
}


int main(int ac, char **av, char **envp) {
	int start = 1;
	int end = 0;
	int flag = 0;
	int	idx = 0;
	int	cmd_count = 0;
	char **cmd = NULL;

	while (av[start] != NULL) {
		flag = 0;
		end = start;
		while (av[end] != NULL && ft_strncmp(av[end], ";", 2) != 0 
				&& ft_strncmp(av[end], "|", 2) != 0) {
			end++;
		}
		if (end != start) {
			if (av[end] != NULL && ft_strncmp(av[end], "|", 2) == 0)
				flag = 1;
			cmd = (char **)malloc(sizeof(char *) * (end - start + 1));
			if (cmd == NULL)
				return (0);
			idx = start;
			cmd_count = 0;
			while (idx < end) {
				cmd[cmd_count] = ft_strdup(av[idx]);
				idx++;
				cmd_count++;
			}
			cmd[cmd_count] = NULL;
			ft_exe(cmd, flag, cmd_count, envp);
			ft_free(cmd);
			cmd = NULL;
		}
		start = end;
		if (av[end] != NULL)
			start++;
	}
	return (0);
}

void	cd_exe(char **cmd, int count) {
	if (count != 2) {
		return ;
	}
	if (chdir(cmd[1]) == -1) {
		return ;
	}
}

void	ft_exe(char **cmd, int flag, int cmd_count, char **envp) {
	int	fd[2];
	int	pid;

	if (flag == 1) {
		pipe(fd);
	}
	if (ft_strncmp(cmd[0], "cd", 3) == 0) {
		cd_exe(cmd, cmd_count);
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
			close(fd[0]);
			close(fd[1]);
		}
		execve(cmd[0], cmd, envp);
		exit(1);
	}
	else {
		waitpid(pid, NULL, 0);
		if (flag == 1) {
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
		}
	}
}