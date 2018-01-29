#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>

#define BUF_SIZE1 5
#define BUF_SIZE2 5

char buf1[] = "text1";
char buf2[] = "text2";

int main()
{
    int fd;

    if((fd = open("file_with_hole.txt", O_WRONLY | O_CREAT, 0644)) < 0)
        perror("creat error");
    if(write(fd, buf1, BUF_SIZE1) != BUF_SIZE1)
        perror("buf1 write error");

    if(lseek(fd, 25, SEEK_END) == -1)
        perror("lseek error");


    if(write(fd, buf2, BUF_SIZE2) != BUF_SIZE2)
        perror("buf2 write error");

    return 0;
}
