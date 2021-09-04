//k&r exercise 5-1
//getint only cares about getting integer from input, if any non-integer, it is pushed back to input for main to deal with it however main wishes

#include <stdio.h>
#include <ctype.h>

int getint(int *);

void main(){

	int a;
	int number = getint(&a);

	if (number!=0)
		printf("%d\n",a);
	else
		printf("Non integer was input, please input only integer\n");
}

int getch(void);
void ungetch (int);

int getint (int *pn){
	int c, sign;

	while(isspace(c=getch())); //skip all white spaces

	if (!isdigit(c) && c!=EOF && c!='+' && c!='-'){
		ungetch(c);
		return 0;
	}

	sign = (c=='-')?-1:1;

	if (c=='+' || c=='-'){
		c=getch();
		if (!isdigit(c)){
			ungetch(c);
			return 0;
		}
	}

	for (*pn=0;isdigit(c);c=getch()){
		*pn = 10 * *pn + (c - '0');
	}

	*pn = *pn * sign;

	if (c!=EOF)
		ungetch(c);
	return c;
}

#define BUFSIZE 100

char buf [BUFSIZE];				//buffer for ungetch
int bufp = 0;					//next free position in buf

int getch (void){				// get a possibly pushed back character
	//return (bufp>0)? buf[--bufp] : getchar();
	return getchar();
}


void ungetch(int c){			//push character back on input
	if (bufp>=BUFSIZE)
		printf("ungetch: too many characters\n");
	else{
		buf[bufp++] = c;
	}
}