/*
 * k&r exercise 1-12: write a program that prints its input one word per line
 * very rudimentary implementation
 */

#include <stdio.h>

void main(){
	
	int c;
	while ((c=getchar())!=EOF){
		if (c==' ' || c=='\n' || c=='\t'){
			printf("\n");	//go to new line to print the next word
		}
		else{
			putchar(c);	//print char to output
		}
	}

}

