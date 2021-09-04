/*
k&r exercise 1-20
modified to k&r exercise 5-11 where input is taken for the tabstop positions and detabed after that

if no input, then use the default tab setting, if there is input then use that

2 10 12 17
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLENGTH 1000
#define TAB 8  //based on systems tabs stop size. default tab stop

void detab(char *s, int argc, char *argv[]); //remove tabs and replace with spaces till next detab
int get_line(char *s,int maxlength);
int atoi(char *s);

void main(int argc, char *argv[]){

	char s[MAXLENGTH];
	while(get_line(s,MAXLENGTH)>0){
		detab(s,argc,argv);
		printf("\n");
	}
}

void detab(char *s,int argc, char *argv[]){

	int count = 0; //counts how many characters before the tab was encountered. Reset it to 0 once you move to next tab stop
	int space;
	argv++;//so that it never points to the program name itself

	while(*s!='\0'){

		if (*s=='\t'){
			if (argc==1){//use the default tab stop if no input arguments exist
				space = TAB - (count%TAB);  //this calculates the number of space until the next tab stop. Use this to print the spaces using putchar
				count = 0;
			}
			else{//use the inputed argument for the tab stop
				space = atoi(*argv) - count;
			}
			while(space--){
				putchar(' ');
			}
			*s++;
		}
		else{
			putchar(*s++);
			count++;

			if (argc>1 && count > atoi(*argv))
				argv++;
		}
	}
}

int get_line(char *s, int maxlength){

	int c;
	char *p=s;
	while(maxlength-- && (c=getchar())!='\n')
		*p++=c;
	
	*p='\0';
	return p-s;
}

int atoi(char *s){

	int c=0;
	while(*s!='\0'){
		c = c*10 + (*s - '0');
		*s++;
	}

	return c;

}