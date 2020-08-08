#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<assert.h>
#include<linux/fs.h>

int main(int argc, char **argv)
{
	int fd, blocksize;
	struct stat st;

	assert(argv[1] != NULL);

	fd = open(argv[1], O_RDONLY);
	if (fd <= 0) {
		perror("error opening file");
		return 0;
	}
	
	if(ioctl(fd, FIGETBSZ, &blocksize)) {
		perror("FIBMAP ioctl failed");
		return 0;
	}	

	fstat(fd, &st);

	printf("%d, %d\n",blocksize, st.st_size);

	
	close(fd);

	return 0;
}
