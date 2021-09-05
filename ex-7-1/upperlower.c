//k&r exercise 7-1 solution: write a program that converts upper case to lower case and vice versa depending on the name it is invoked with

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void main(int argc, char *argv[]){
	
	printf("Hello World!\n");
	if (argc < 2){
		printf ("%s\n","Need to enter either tolower or tohigher as an argument");
		exit(1);
	}
	else if (argc > 2){
		printf ("%s\n","Too many arguments");
		exit(2);
	}
	else{
		if (strcmp(argv[1],"tolower")!=0 && strcmp(argv[1],"tohigher")!=0){
				printf("%s\n","The argument needs to be either tolower or tohigher");
				exit(3);
		}
	}
	
	int c;
	while ((c=getchar())!=EOF){
		
		if(strcmp(argv[1],"tolower")==0)
			putchar (tolower(c));    //tolower and tohigher functions are from ctype.h header
		else 
			putchar (toupper(c));
	}
	exit(0);		//exit status 0 means entire program is executed as expected
}
