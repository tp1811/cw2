#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>
#define M_PI 3.14159265358979323846

int main(int argc, char *argv[])	
{	
float freq;
short samples [2];
//short samples [1024];	// implement 512 samples stereo buffer
unsigned buffer_size=sizeof(samples);	// size in bytes of  one stereo sample (4 bytes)
int t = 0;
int counter = 0;	// variable to count 

freq = 200;	// set default frequency
if (argc>1){
			 freq = atoi(argv[1]);	// set frequency
		 }

	while(1){
		// Buffer containing one stereo sample sample (left and right, both 16 bit).
		
		for (int j=0; j<512; j++){
			samples[(2*j)+(counter*512)]=(short)30000*sin((j+(512*counter))*2*M_PI*freq/44100);
			samples[(2*j)+(counter*512)+1]=(short)30000*sin((j+(512*counter))*2*M_PI*freq/44100);
		}
		
		samples[0]=(short)30000*sin(t*2*M_PI*freq/44100);	// generate sample
		samples[1]=(short)30000*sin(t*2*M_PI*freq/44100);	// generate sample
		
		int done=write(STDOUT_FILENO, samples, buffer_size);
		if(done<0){
			fprintf(stderr, "%s : Write to stdout failed, error=%s.", argv[0], strerror(errno));
			exit(1);
		}else if(done!=buffer_size){
			fprintf(stderr, "%s : Could not read requested number of bytes from stream.\n", argv[0]);
		}
		t = t+1;
	}
	counter = counter + 1;
	return 0;
}
