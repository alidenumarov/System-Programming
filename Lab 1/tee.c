#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main() {
    int len = BUF_SIZE;
    char str[BUF_SIZE],str1[BUF_SIZE],str2[BUF_SIZE];
    int read;
    ssize_t wr;
    char buf[BUF_SIZE] = "some_text";
    printf("Enter the command:\n");
    scanf("%s %s %s",str,str1,str2);

    read = open(str2, O_CREAT | O_RDWR | O_APPEND, 0644);
    if(read == -1) {
        perror("opening error in reading file");
        exit(EXIT_FAILURE);
    }

    if(lseek(read, 0, SEEK_END) == -1)
        perror("error in lseek");

    if(write(read,buf, len)!= len)
       perror("error in writing");

 return 0;
}
