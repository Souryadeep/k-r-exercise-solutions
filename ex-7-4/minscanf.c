/*
k&r exercise 7-4: write a private version of scanf analogous to minprintf from the previous section
scanf stops when fomrat string is exhausted or some input fails to match the control specification
this is a very rudimentary version
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define MAXWORD 100

int minscanf(char *format, ...);

void main(int argc, char *argv[]){

	int ival;
	float dval;
	unsigned uval;
	char *p,*sval,cval;
	
	sval = (char *)malloc(MAXWORD);		//without this malloc for the char array where only pointer was defined but not array, program does not work. IMP!

	//get int/dec input and print it
	minscanf("%d",&ival);
	printf("The value of the integer is: %d\n",ival);

	//get double input and print it
	minscanf("%f",&dval);
	printf("The value of the float is: %f\n",dval);

	//get oct input and print it
	minscanf("%o",&ival);
	printf("The value of the octal is: %o\n",ival);

	//get hex input and print it
	minscanf("%x",&ival);
	printf("The value of the hex is: %x\n",ival);


	//get unsigned int input and print it
	minscanf("%u",&uval);
	printf("The value of the unsigned int is: %u\n",uval);

	//get single char input and print it
	minscanf("%c",&cval);
	printf("The value of the char is: %c\n",cval);

	//get string input and print it
	minscanf("%s",sval);
	printf("The value of the char is: %s\n",sval);
}

int minscanf(char *fmt, ...){

	va_list ap;		//arg pointer of variable list type from stdarg.h

	char *p, *sval;	//p is the pointer to scan through *fmt
	int *ival;		//integer value for %d
	float *dval;	//float value for %f
	unsigned *uval;
	char *cval;



	va_start(ap,fmt);	//makes ap point to the first unnamed argument. must be called once before ap is used. this is a macro

	for(p=fmt;*p;p++){

		if(*p=='%'){

			switch(*++p){
				case 'd':
				ival = va_arg(ap,int *);
				scanf("%d",ival);
				break;
				case 'f':
				dval = va_arg(ap,float *);
				scanf ("%f",dval);
				break;
				case 'o':
				ival = va_arg(ap,int *);
				scanf ("%o",ival);
				break;
			case 's':
				printf("here\n");
				sval = va_arg(ap,char *);
				scanf("%s",sval);
				break;
			case 'x':
			case 'X':
				ival = va_arg(ap,int *);
				scanf("%x",ival);
				break;
			case 'u':
				uval = va_arg(ap,unsigned *);
				scanf("%u",uval);
				break;
			case 'c':
				cval = va_arg(ap,char *);
				scanf("%1s",cval);			//scanf does suppresses skip over white spaces so the newline from earlier causes it to terminate there. Hence keep white space followed by %c to collect the first non white space char in input stream OR use %1s
				break;
			/*case 'e':
				dval = va_arg(ap,double);
				break;*/
			default:
				break;
			}
		}

	}

	va_end(ap);

}