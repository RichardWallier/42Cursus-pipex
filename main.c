#include "libft/libft.h"

int main(int argc, char *argv[])
{
	int **fd;
	int fd2[2][2];

	fd = (int **)malloc(2 * (sizeof(int *)));
	fd[0] = (int *)malloc(2 * sizeof(int));
	fd[1] = (int *)malloc(2 * sizeof(int));
	pipe(fd[0]);
	pipe(fd[1]);

	pipe(fd2[0]);
	pipe(fd2[1]);

	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);

	close(fd2[0][0]);
	close(fd2[0][1]);
	close(fd2[1][0]);
	close(fd2[1][1]);
	return (0);
}
