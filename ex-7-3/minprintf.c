/*
handling variable length argument lists
std header stdarg.h is used for this. Following macros help to implement the features required:
	- va_list used to declare a variable that refers to each argument in turn 
	- ap is the argument pointer of type va_list
	- va_start initialized ap to point to first unnamed argument. Must have atleast one argument. final arg is used to get va_start started
	- each call to va_arg returns one arg and steps ap to the next arg. va_arg uses the type name to determine the return type and step size to take
	- va_end will do the necessary cleanup

proper decleraration for printf is:
	- int printf (char *fmt, ...)

k&r exercise 7-3: revise minprintf to handle more of the other facilities of printf

*/

#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);	// ... needs to come at end of argument list and indicates number and types of arguments may vary

void main(){

	minprintf("There are %c people in this room and we are expecting donations worth %e today",'a',1e+2);

	/*double x = 1e-2;
	printf("%.0e\n",x);
	*/

}

void minprintf(char *fmt, ...){

	va_list ap;		//va_list type defined in stdarg.h header. ap is the argument pointer of this type
	char *p, *sval;	//p is the pointer to scan through *fmt
	int ival;		//integer value for %d
	double dval;	//float value for %f
	unsigned uval;

	va_start(ap,fmt);	//makes ap point to the first unnamed argument. must be called once before ap is used. this is a macro

	for (p=fmt;*p;p++){
		if (*p!='%'){
			putchar(*p);
			continue;
		}

		switch(*++p){
			case 'd':
				ival = va_arg(ap,int);
				printf("%d",ival);
				break;
			case 'f':
				dval = va_arg(ap,double);
				printf("%f",dval);
				break;
			case 's':
				for (sval=va_arg(ap,char *);*sval;sval++){
					putchar(*sval);
				}
				break;
			case 'o':
				ival = va_arg(ap,int);
				printf("%o",ival);
				break;
			case 'x':
				ival = va_arg(ap,int);
				printf("%x",ival);
				break;
			case 'X':
				ival = va_arg(ap,int);
				printf("%X",ival);
				break;
			case 'u':
				uval = va_arg(ap,unsigned);
				printf("%u",uval);
				break;
			case 'c':
				ival = va_arg(ap,int);
				putchar(ival);
				break;
			case 'e':
				dval = va_arg(ap,double);
				printf("%.2e",dval);
				break;
			default:
				putchar(*p);
				break;
		}
	}
	printf("\n");
	va_end(ap);		//clean up when done. But what cleanup is being done?

}