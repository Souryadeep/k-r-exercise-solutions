//k&r exercise 5-2
//does not take care of all corner cases, such as 123e, is handled as 123.00, instead of invalid input.


#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

int getfloat(float *);

void main(){

	float a;
	int number = getfloat(&a);

	if (number!=0)
		printf("%.2f\n",a);
	else
		printf("Non floating point number was input, please input only floating point numbers\n");
}

int getch(void);
void ungetch (int);

int getfloat (float *pn){
	int c,sign;
	float power;
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

	for (*pn=0.0;isdigit(c);c=getch()){
		*pn = 10.0 * *pn + (c - '0');
	}

	if (c=='.')
		c=getch();

	for (power=1.0;isdigit(c);c=getch()){
		*pn = 10.0 * *pn + (c - '0');
		power= power*10.0;
	}


	*pn = *pn * sign/power;

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