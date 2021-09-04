//k&r exercise 5-5

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100

//char *strncpy_(char *s, char *t, int n);
//char *strncat_(char *s, char *t, int n);
int strncmp_(char *s, char *t, int n);

void main(){

	int n = 26;
	char s[MAXLENGTH] = "Doing fine, how about you?"; //since it is within a function scope and is not static and does not have an initializer, so the values by default in this char array are garbage
	char t[MAXLENGTH] = "Doing fine, how about you?";

	/*char *p = strncpy_(s,t,n);

	while (*p!='\0')
		printf("%c",*p++);

	char *p = strncat_(s,t,n);
	printf("\n");

	while (*p!='\0')
		printf("%c",*p++);
	*/

	int cmp = strncmp_(s,t,n);

	if (!cmp)
		printf("Strings are equivalent\n");
	else if(cmp<1)
		printf("String t is lexically greater than string s\n");
	else
		printf("String s is lexically greater than string t\n");
}


int strncmp_(char *s, char *t, int n){

	while (n-- && *s!='\0' && *t!='\0'){
		if (*s<*t)
			return -1;
		else if (*s>*t)
			return 1;

		s++;t++;  //wonder if comma is allowed between the 2 statements?
	}

	return 0;
}

/*char *strncat_(char *s, char *t, int n){

	char *p=s;
	while(*p)
		p++;

	while(n-- && *t)
		*p++ = *t++;

	*p='\0';

	return s;

}*/

/*char *strncpy_(char *s, char *t, int n){

	int i=1;
	while(i<=n && *t!='\0'){
		*s = *t;
		s++;
		t++;
		i++;
	}

	while (i<=n){
		*s='\0';
		s++;
		i++;
	}

	if (*t!='\0'){
		*s='\0';
	}
	else if (i>n)
		*s='\0';

	return s-n;
}*/