#include<stdio.h>

int main(int argc, char **argv)
{
	int fd;

	assert(argv[1] != NULL);

	fd = open(argv[1], O_RDONLY);
	if (fd <= 0) {
		perror("error opening file");
		return 0;
	}

	
	fclose(fd);

	return 0;
}
