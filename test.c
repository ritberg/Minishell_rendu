#include <fcntl.h>
#include "libft/includes/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/errno.h>
#include <string.h>

int	main(void)
{
	char *file = "file";
	char *file1 = ".file1";
	char *file2 = "../file2";
	char *file3 = ".file3";
	char *file4 = ".file4";
	char *file5 = ".file5";
	char *file6 = ".file6";
	int	fd_file;
	int	fd_file1;
	int	fd_file2;
	int	fd_file3;
	int	fd_file4;
	int	fd_file5;
	int	fd_file6;
	int	save_fd_out;


	fd_file = open(file, O_WRONLY | O_CREAT | O_TRUNC , 0644 );
	fd_file1 = open(file1, O_WRONLY | O_CREAT | O_TRUNC , 0644 );
	fd_file2 = open(file2, O_WRONLY | O_CREAT | O_TRUNC , 0644 );
	fd_file3 = open(file3, O_WRONLY | O_CREAT | O_TRUNC , 0644 );
	fd_file4 = open(file4, O_WRONLY | O_CREAT | O_TRUNC , 0644 );
	fd_file5 = open(file5, O_WRONLY | O_CREAT | O_TRUNC , 0644 );
	fd_file6 = open(file6, O_WRONLY | O_CREAT | O_TRUNC , 0644 );

	save_fd_out = dup(STDOUT_FILENO);
	dup2(fd_file, STDOUT_FILENO);

	ft_printf("fd_file = %d\n", fd_file);
	ft_printf("fd_file1 = %d\n", fd_file1);
	ft_printf("fd_file2 = %d\n", fd_file2);
	ft_printf("fd_file3 = %d\n", fd_file3);
	ft_printf("fd_file4 = %d\n", fd_file4);
	ft_printf("fd_file5 = %d\n", fd_file5);
	ft_printf("fd_file6 = %d\n", fd_file6);
	ft_printf("save_fd_out = %d\n", save_fd_out);

	close(fd_file);
	ft_putstr_fd("coucou\n", STDOUT_FILENO);

	dup2(save_fd_out, STDOUT_FILENO);
	ft_dprintf(STDOUT_FILENO,"hello\n");

	int err = open("errorfile", O_WRONLY | O_CREAT | O_TRUNC , 0644 );
	int save_fd_err = dup(STDERR_FILENO);
	dup2(err, STDERR_FILENO);
	close(err);

	access("refdw", F_OK);
	ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
	access("refdw", F_OK);
	ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
	access("refdw", F_OK);
	ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
	access("refdw", F_OK);
	ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
	
	dup2(save_fd_err, STDERR_FILENO);
	access("refdw", F_OK);
	ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
}
