//k&r exercise 5-3
//need to revisit this problem, have the same question as https://cloudstack.ninja/thomas/kr-c-book-exercise-5-3-strcat-example/

#include <stdio.h>
#include <string.h>
#define MAX 100
void *strcat_(char *s, char *t);

void main(){

	
	char s[MAX] = "hello ";
	char t[MAX] = "there!";

	char *p=s;
	char *q=t;

	//printf("%c\n",*p);

	strcat_(p,q);

	printf("%s\n",s);
}

void *strcat_(char *s,char *t){
	//printf("%c\n",*s);
	while(*s)
		s++;
	while(*s++ = *t++);

}


/*#include <stdio.h>

void *strcatsnot(char *s, const char *t);

void *strcatsnot(char *s, const char *t)
{
    while (*++s)
        ;
    while (*s++ = *t++)
        ;
}

int main()
{
    char snot[40] = "why so ";
    char blah[] = "cereal?";
    strcatsnot(snot, blah);
    printf("%s\n", snot);
    return 0;
}*/