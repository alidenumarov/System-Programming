#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 8192
#define BUF_SIZE 8192

int main() {
    char buf[1];
    FILE *stdin = fopen("maxline.txt", "r");
    FILE *stdout = fopen("maxline2.txt", "w+");

    while (fgets(buf, 1, stdin) != NULL)
    if (fputs(buf, stdout) == EOF) {
        perror("writing error");
    }
    // print about output error

    if (ferror(stdin)) {
        perror("writing error");
    }
    // print about input error
    exit(0);

    return 0;
}

