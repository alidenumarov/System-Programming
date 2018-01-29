#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main() {
	ssize_t numRead;
	char buf[BUF_SIZE];
	int input = open("read_t1.txt", O_RDONLY);
	if(input == -1) {
		perror("opening error in first file");
		exit(EXIT_FAILURE);
	}
	int output = open("write_t1.txt", O_WRONLY | O_CREAT, 0644);
	if(output == -1) {
		perror("Error in opening second file");
		exit(EXIT_FAILURE);
	}
	int buf_num = 0;
	int len = BUF_SIZE;

	while(len > 0 && (numRead = read(input, buf, len)) > 0) {
		if(numRead == -1) {
			if(errno == EINTR)
				continue;
			perror("read");
			break;
		}
		len -= numRead;
		buf_num += numRead;
		if(write(output, buf, buf_num) != buf_num) {
			perror("Error in writing");
			exit(EXIT_FAILURE);
		}
	}

	if(numRead == -1) {
		perror("Read error");
		exit(EXIT_FAILURE);
	}

	int ch_in = close(input);
	int ch_out = close(output);
	if(ch_in == -1) {
		perror("Close error input");
	}
	if(ch_out == -1) {
		perror("Close error output");
	}
	return 0;
}
