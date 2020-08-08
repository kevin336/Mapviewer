#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<assert.h>
#include<linux/fs.h>

int main(int argc, char **argv)
{
	int fd, blocksize;

	assert(argv[1] != NULL);

	fd = open(argv[1], O_RDONLY);
	if (fd <= 0) {
		perror("error opening file");
		return 0;
	}
	
	ioctl(fd, FIGETBSZ, &blocksize);

	printf("%d\n",blocksize);

	
	close(fd);

	return 0;
}
