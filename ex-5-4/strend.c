//k&r exercise 5-4

#include <stdio.h>
#include <string.h>

#define MAXCOUNT 100

int strend(char *s, char *t);   //returns 1 if t is present at the end of s, else returns 0

void main(){

	char s[MAXCOUNT] = "Hello how are you?"; //char array is initialized with size and also with characters... this is allowed. need to note
	char t[MAXCOUNT] = "you?";               //assigning the string to declared and defined char array is not allowed. char s[MAXCOUNT] and s = "string" is not allowed. throws an error
											 //error: assignment to expression with array type”
	int result = strend(s,t);

	if (result)
		printf("String t was found at end of s\n");
	else
		printf("String t was not found at end of s\n");

}

int strend(char *s, char *t){

	while (*s!='\0' && *s!=*t)
		s++;
	if (!*s)
		return 0;

	while (*s++==*t++ && *s!='\0' && *t!='\0');

	if(*s == '\0' && *t=='\0')
		return 1;
	else
		return 0;


}

