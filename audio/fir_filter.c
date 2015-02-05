#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
 
#include <unistd.h>
 
#define PI 3.1415926535
// FIR functino doesn't work
 
int main(int argc, char *argv[])
{          
           
    FILE *fp1;
 
    fp1=fopen(argv[1],"r");
 
    int no_coeffs = 0;
 
    char temp = getc(fp1);
    while (temp !=EOF){
        if (temp =='\n')
			no_coeffs = no_coeffs+1;
            temp = getc(fp1);
    }
    rewind(fp1);
           
    int i = 0;
    double filterbuffer[no_coeffs];
 
    while (!feof(fp1)){
        fscanf(fp1,"%lf",&filterbuffer[i]);
        i++;
            }
 
    fclose(fp1);
	
	double coef_buffer[no_coeffs];	// stores coefficients
	double input_buffer[2*no_coeffs]; //buffer to inputs
	float out_buffer[2];	// output array stores a single sample
	double acc_1, acc_2;	// accumulator for left and right channels
	int j;
 
    while(1){                                
            //Read one stereo sample from input
           
        int got=read(STDIN_FILENO, input_buffer, 2*sizeof(float));	
        if(got<0){
            fprintf(stderr, "%s : Read from stdin failed, error=%s.", argv[0], strerror(errno));
            exit(1);
        }else if(got==0){
			break;   // end of file
        }/*else if(got!=cbBuffer){
            fprintf(stderr, "%s : Did not receive expected number of bytes.\n", argv[0]);
            exit(1);
        }*/
		acc_1 = 0;	// re-initialise accumulators
		acc_2 = 0;
		for(i=0;i<no_coeffs;i++){
			acc_1 = acc_1 + (coef_buffer[i]*input_buffer[2*i]);	//MAC left
			acc_2 = acc_2 + (coef_buffer[i]*input_buffer[(2*i)+1]);	// MAC right
		}
		out_buffer[0] = acc_1;	// place results in output buffer
		out_buffer[1] = acc_2;
		
		for (j=0;j<no_coeffs;j++){
			input_buffer[no_coeffs-1-j]=input_buffer[no_coeffs-2-j];
		}
		
     
		int done=write(STDOUT_FILENO, out_buffer, 2*sizeof(float));	// stdout
		if(done<0){
			fprintf(stderr, "%s : Write to stdout failed, error=%s.", argv[0], strerror(errno));
			exit(1);
		}/*else if(done!=cbBufferOut){
			fprintf(stderr, "%s : Could not read requested number of bytes from stream.\n", argv[0]);
    }*/
    }
 
        return 0;
}