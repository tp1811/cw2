#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
 
#include <unistd.h>
 
// combines the 2 input streams into 1 output stream  
int main(int argc, char *argv[])
{          
 
    FILE *fp1=fopen(argv[1],"r");	// file 1 pointer
    FILE *fp2=fopen(argv[2],"r");	// file 2 pointer
    int16_t samples_1[2], samples_2[2];	// buffer to store I/P streams separately
	int16_t samples_out[2];	// buffer for O/P stream
	unsigned buffer_size = sizeof(samples_1);
			
    if ((fp1 == NULL) || (fp2 == NULL))	// error condition
    printf("File cannot be opened");
 
    while(1){
        int gotA = fread(samples_1,buffer_size,1,fp1);	// read stereo value from I/P 1
        int gotB = fread(samples_2,buffer_size,1,fp2);	// read stereo value from I/P 2
           
        samples_out[0] = 0.5*samples_1[0] + 0.5*samples_2[0];	// combine samples for left channel
        samples_out[1] = 0.5*samples_1[1] + 0.5*samples_2[1];	// combine samples for right channel
                       
        // Copy one sample to output
        int done=write(STDOUT_FILENO, samples_out, buffer_size);
        if(done<0){
            fprintf(stderr, "%s : Write to stdout failed, error=%s.", argv[0], strerror(errno));
            exit(1);
        }else if(done!=buffer_size){
            fprintf(stderr, "%s : Could not read requested number of bytes from stream.\n", argv[0]);
        }
    }
 
    fclose(fp1);
    fclose(fp2);
    return 0;
}
