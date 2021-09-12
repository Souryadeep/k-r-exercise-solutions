/*
 * write a program to print a histogram of the frequencies of different characters in its input
 */

#include <stdio.h>

#define CODES 128

void main(){

	int c, asciiLookup[CODES];	//total of 128 regular ASCII lookup codes held per position of this array, starting from 0 which is NULL

	for (int i=0;i<CODES;++i) asciiLookup[i]=0;	//initialize occurence of all characters to 0

	while ((c=getchar())!='\n'){
		++asciiLookup[c];
	}
	
	for (int i=0;i<CODES;i++){
		if (asciiLookup[i]>0){
			printf("Occurence of character %c is: ",i);
			for (int j=0;j<asciiLookup[i];j++)
				putchar('-');
			putchar('\n');	
		}
	}
	
	

}
