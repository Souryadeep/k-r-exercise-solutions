/*
	k&r exercise 1-13: write a program to print a histogram of the lengths of words in its input. it is easy to draw the hist with bars horizontal, a vertical orientation is more challenging
	---> implementation below is using horizontal bars
	---> try the vertical solution yourself and mail me if you cannot solve it
*/

#include <stdio.h>


#define MAXWORDLENGTH 100 //max length of a word allowed is 100, therefore the array created should be of that length
#define IN 1
#define OUT 0 //used for the state machine in wordcount.c program

void main(){

	int c,i,wlen,j,state;
	int wlenOccur[MAXWORDLENGTH];

	for (i=0;i<MAXWORDLENGTH;++i) wlenOccur[i]=0;

	state = OUT;
	wlen = 0;

	while ((c=getchar())!='\n'){

		if (c=='\n' || c == '\t' || c==' '){

			state = OUT;
			if (wlen !=0){
				++wlenOccur[wlen];
				wlen = 0;
			}

		}
		else if (state == OUT){
			state = IN;
			++wlen;
		}
		else{
			++wlen;
		}

	}

	for (i=0;i<MAXWORDLENGTH;++i){
		if(wlenOccur[i]!=0){
			printf("Occurence of word length: %d:  ", i);
			for (j=0;j<wlenOccur[i];++j){
				putchar('-');
			}
			putchar('\n');

		}
	}

}