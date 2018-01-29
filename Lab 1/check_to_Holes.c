#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFERSIZE 1024

int main () {
    struct stat fileStat;
    if ((stat("file_with_hole.txt", &fileStat)) < 0) {
        fprintf(stderr, "Stat error: %s\n", strerror(errno));
    } else {
        printf("Logical blocks num is %ld\n", fileStat.st_size );
        printf("Physical blocks num is %ld\n", fileStat.st_blocks);
        if (fileStat.st_size > fileStat.st_blocks) {
            int holes = fileStat.st_size - fileStat.st_blocks;
            printf("There are HOLES in file!");
        }
    }

    return 0;
}
