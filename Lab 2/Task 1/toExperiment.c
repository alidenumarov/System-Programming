#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 8192

int main() {
    ssize_t ret_in, ret_out;
    int arr_bufSizes[5] = {1, 100, 512, 1024, 4096};
    long long arr_dataSize[5] = {4865, 101482, 1023385, 2047705, 5119730};
    double sPerByte = 0.00001;
	char to_read[5][100] = {"r1.txt", "r2.txt", "r3.txt", "r4.txt", "r5.txt"};
	char to_write[5][100] = {"w1.txt", "w2.txt", "w3.txt", "w4.txt", "w5.txt"};
    int i, j;
    printf("Let consider that 1 byte data done for 0.1ms with 1 buffer size, so:\n");

    for(i = 0; i < 5; i++) {

        printf("          %s", to_read[i]);

    }
    printf("\n\nbuf size\n");
    for(i = 0; i < 5; i++) {
		printf("%d", arr_bufSizes[i]);

        for(j = 0; j < 5; j++) {

			double result = (0.01 * arr_dataSize[j]) / arr_bufSizes[i];
            printf("          %.3lfms", result);
            /* Copy process */
            char buffer[arr_bufSizes[i]];
            int input = open(to_read[j], O_RDONLY);
			if(input == -1) {
				perror("opening error in read file");
				exit(EXIT_FAILURE);
			}
			int output = open(to_write[j], O_WRONLY | O_CREAT, 0644);

            while((ret_in = read (input, &buffer, arr_bufSizes[i])) > 0){
                ret_out = write (output, &buffer, (ssize_t) ret_in);
                if(ret_out != ret_in){
                    perror("write");
                    return 0;
                }
            }
            int ch_in = close(input);
            int ch_out = close(output);
            if(ch_in == -1) perror("Close error input");
            if(ch_out == -1) perror("Close error output");
        }
        printf("\n");
    }
    printf("Written succesfully!");
    return 0;
}
