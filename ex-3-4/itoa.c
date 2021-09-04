//k&r exercise 3-4

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>


//itoa: convert n to characters in s

#define MAXLENGTH 100  //maxlength of the char array that stores the converted integer

void itoa_(int n, char s[],int width);
void reverse(char s[]);


void main(){

	int c;
	int i=5400;
	char s[MAXLENGTH];
	/*while((c=getchar())!='\n' && i < MAXLENGTH)       //NEED TO CHECK HOW TO ACCEPT INTEGER INPUT FROM CMD LINE
		s[i++]=c;
	*/
	printf("%d\n", INT_MIN);
	itoa_(i,s,10);


}

void itoa_(int n, char s[],int width){

	int i, sign;
/*
	if ((sign = n)<0)  //record the sign and make n positive for the conversion
		n=-n;
*/
	sign=n;
	i=0;
	do{					// generate digits in the reverse order
		s[i++]= abs(n%10) + '0';			//this is handling for the largest negative number in 2's complement system since -largest negative = itself
	}while((n/=10));         //remember that the semicolon is required at this point. The while is changed to n/10 as for largest negative number, loop would end in the beginning

	if(sign<0)
		s[i++]='-';
	while(i<width){
		s[i++]=' ';
	}

	s[i]='\0';
	reverse(s);
	//printf("%d\n", strlen(s));

}


void reverse(char s[]){

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
}