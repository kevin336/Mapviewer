#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<assert.h>
#include<linux/fs.h>

int main(int argc, char **argv)
{
	int fd, blocksize, blkcnt;
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

	if(fstat(fd, &st)){
		perror("fstat error");
		return 0;
	}

	blkcnt = (st.st_size + blocksize - 1) / blocksize;
	
	printf("File %s size %ld blocks %d blocksize %d\n",
			argv[1], st.st_size, blkcnt, blocksize);

	
	close(fd);

	return 0;
}
