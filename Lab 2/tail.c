#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 8192

int main() {
    char ch = 0;
    int num_lines = 0;

    FILE *file = fopen("tail.txt", "r");

    while(!feof(file)) {
        ch = fgetc(file);
        if(ch == '\n') {
            num_lines++;
        }
    }

    fseek(file, 0, SEEK_SET);

    int length = 200;
    char line[length];
    char *c = 0;
    int line_count = 0;

    printf("There are %d lines\n", num_lines);

    int num_lines_to_read;
    printf("Enter number of lines: ");
    scanf("%d", &num_lines_to_read);

    if(num_lines_to_read > num_lines) {
        printf("Enter less than %d value !", num_lines);
    }

    do {
        c = fgets(line, length, file);
        if(c != NULL && (line_count >= num_lines - num_lines_to_read)) {
            printf("%s", line);
        }
        line_count++;
    } while(c != NULL);

    return 0;
}
