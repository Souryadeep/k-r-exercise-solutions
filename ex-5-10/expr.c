/*
k&r exercise 5-10: where input for the reverse polish calculator is now from cmd line input
problem with this is when running on the windows command line, the * results in taking all the directory files as input
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


#define MAXOP 100    //max size of operator or operand
#define NUMBER '0'   //signal that a number was found

int getop(char *);
void push(double);
double pop(void);    //better to use void when no arguments for the function

void main(int argc, char *argv[]){

	int type;  		//is it an operator or operand or something else
	double op2,op1;

	while (--argc){			//left to right evaluation of the || statement so check EOF first

		type = getop(*++argv);
		switch(type){
			case NUMBER:
				push (atof(*argv)); //atof is part of stdlib.h library
				break;
			case '+':
				push (pop()+pop());
				break;
			case '*':
				push (pop()*pop());
				break;
			case '-':
				op2 = pop();
				push (pop()-op2);
				break;	
			case '/':
				op2 = pop();
				if (op2)
					push (pop()/op2);
				else
					printf("error: zero divisor\n");
				break;
			default:
				printf("error: unknown command %s\n",*argv);
				break;
		}

	}
	printf("\t%.8g\n",pop());

}

#define MAXVAL 100

int sp = 0;              //next free stack position
double val[MAXVAL];      //value stack


void push(double f){
	if (sp<MAXVAL)
		val[sp++]=f;
	else
		printf("error: stack full, can't push %g\n",f);
}

double pop(void){
	if (sp>0){
		//printf("Stack pointer position: %d\n",sp );
		return val[--sp];
	}
	else{
		printf("error: stack empty\n");
		return 0.0;
	}
}

#include <ctype.h>

int getop(char *s){
		

	if (!isdigit(*s) && *s!='.'){		//not a number
		return *s;
	}

	if (isdigit(*s))      		//collect integer portion
		while(isdigit(*s++)) 
			;
	if (*s == '.'){				//collect fraction portion
		while(isdigit(*s++))
			;
	}

	return NUMBER;

}
