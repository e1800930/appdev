#include <stdio.h>
#include <math.h>
#include "sound.h"
#include "screen.h"

void showID(char*idname, char *id){
	int i;
	printf("%s : ",idname);
	for(i=0;i<4;i++){
		printf("%c",id[i]);
		puts("");
	}
}

//this function gets one second of samples (16000), and calculats
//80 pieces pof decibel values, we know we need to calculate one decibel value 
//from 200 sample, decibel value is calculated by RMS formula
void displayWAVDATA(short s[]){
	double rms[80];
	int db[80];//fro decibal values
	short *ptr = s;//we use a pointer, pointing to the beginning of array
	int i,j; // for the nested loop counters, outer loop repeats 80 times
		//inner loop repeats 200 times

	for(i=0;i<80;i++){
		double sum = 0;//accumulate sum of square
		for(j=0;j<200;j++){
			sum += (*ptr) * (*ptr);
			ptr++; //poiting to the next sample
		}
		rms[i] = sqrt(sum/200);
		db[i]=20*log10(rms[i]);
#ifdef DEBUG
		printf("rms[%d] = %f\n",i,rms[i]);
#endif
	}
#ifndef DEBUG
	barChart(db);
#endif
}

void displayWAVHDR(struct WAVHDR h){
#ifdef DEBUG
	showID("ID",h.ChunkID);
	printf("Chunk size: %d\n",h.ChunkSize);
	showID("Format",h.Format);
	showID("Subchunk1ID",h.Subchunk1ID);
	printf("Subchunk1 size: %d\n",h.Subchunk1Size);
	printf("Audio format: %d\n",h.Format);
	printf("Num. of channels: %d\n",h.NumChannels);
	printf("Sample Rate: %d\n",h.SampleRate);
	printf("Byte Rate: %d\n",h.ByteRate);
	printf("Block align: %d\n",h.BlockAlign);
	printf("Bits per sample: %d\n",h.BitsPerSample);
	showID("Subchunk2ID ",h.Subchunk2ID);
	printf("Subchunk2 size: %d\n", h.Subchunk2Size);
#else 
	setColors(RED, bg(BLUE));
	printf("\033[1;1H");
	printf("test.wav                    \n");
	setColors(YELLOW,bg(GREEN));
	printf("\033[1;21H");
	printf("Sample rate= %d          \n",h.SampleRate);
	setColors(WHITE, bg(CYAN));
	printf("\033[1;61H"); 
	printf("Duration=%.2f            \n",(float)h.Subchunk2Size/h.ByteRate);
#endif
}
