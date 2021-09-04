//k&r exercise 4-12

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>


//itoa: convert n to characters in s, but use recursion instead of the do while loop in exercise 3-4 for itoa

#define MAXLENGTH 100  //maxlength of the char array that stores the converted integer

void itoa_recursive(int n);
//void reverse(char s[]);


void main(){

	int c;
	int i=-2147483648;
	char s[MAXLENGTH];
	/*while((c=getchar())!='\n' && i < MAXLENGTH)       //NEED TO CHECK HOW TO ACCEPT INTEGER INPUT FROM CMD LINE
		s[i++]=c;
	*/
	printf("%d\n", INT_MIN);
	itoa_recursive(i);
}

void itoa_recursive(int n){
	//static int i;   // for static and extenal variables, the initializer must be a constant, unlike for automatic and register variables where it can be a variable.
	//i=n;
	// printf("%d\n",n);
	if (n<0 && n/10==0){
		putchar('-');
	}

	if (n/10){
		//printf("%d\n",n);
		itoa_recursive(n/10);
	}
	putchar(abs(n%10) + '0');
}


/*void reverse(char s[]){

	char reversed[MAXLENGTH];
	int i=0;
	int j = strlen(s);
	while(s[i]!='\0'){
		reversed[i] = s[j-1-i];
		i++;
	}
	s[i]='\0';
	//printf("%s\n",reversed);		this prints past the null character, not sure if it is being comnsidered as a string, need to find out

	for (i=0;i<j;i++){
		printf("%c",reversed[i]);
	}
}*/