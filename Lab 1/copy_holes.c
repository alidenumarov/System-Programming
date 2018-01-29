#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFERSIZE 1024

int main(int ac, char *av[])
{
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];

    if((in_fd = open("file_with_hole.txt", O_RDONLY)) == -1 ) {
        perror("Error in reading");
    }

    if((out_fd = open("file_with_hole_Copy.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664)) == -1 ) {
        perror("Error in writing");
    }

    int cur,prev = 0;

    while( (n_chars = read(in_fd, buf, BUFFERSIZE)) > 0 ) {
        if(&buf[cur] != NULL) {
            if( write(out_fd, buf, n_chars) != n_chars ) {
              perror("Error in writing");
            }
        } else {
            if((cur = lseek(out_fd, cur, SEEK_CUR)) < 0) {
                fprintf(stderr, "Seek error: %s\n", strerror(errno));
            }
            if ((lseek(in_fd, cur, SEEK_CUR)) < 0) {
                fprintf(stderr, "Seek error: %s\n", strerror(errno));
            }
        }

        if( n_chars == -1 ) {
            perror("Error in reading");
        }
    }

    if( close(in_fd) == -1 || close(out_fd) == -1 ) {
        perror("Error in closing");
    }
    return 0;
}
