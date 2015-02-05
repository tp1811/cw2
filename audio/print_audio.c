#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>

int main(int argc, char *argv[])
{
	int index = 0;	// initialise index
	int left, right;	// left & right channels
	float time = 0;
	float sample_rate = 44100;	// sample rate
	FILE *f = fopen("print_audio.csv", "w");	// pointer to file
	while(1){
		int16_t samples[2];	// array to store samples
		unsigned buffer_size = sizeof(samples);	// size of buffer
		int got=read(STDIN_FILENO, samples, buffer_size);	// read first 2 samples
		if(got==0){
			break;	 // end of file condition
		}
		left = samples[0];
		right = samples[1];
		time = (float)index/sample_rate;
		// printf("%f\n", time);	// testing
		fprintf(f, "%d, %f, %d, %d\n", index, time, left, right);	// print to csv
		index=index+1;	// increment for next loop
	}
	return 0;
	fclose(f);
}