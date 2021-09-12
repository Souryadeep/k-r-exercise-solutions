/*
	k&r exercise 1-8: write a program to count blanks, tabs and newlines
*/

#include <stdio.h>

void main(){

	long blanks, tabs, newline;
	int c;
	blanks = 0;
	tabs = 0;
	newline = 0;
	while ((c=getchar())!=EOF){
		if (c == ' ')
			++blanks;
		else if (c == '\n')
			++newline;
		else if (c == '\t')
			++tabs;
		if (c == '\n')
			printf("newlines: %ld\t tabs: %ld\t blanks: %ld\n",newline,tabs,blanks);
			
	}
	//printf("%ld\n",nc);
}