/*k&r exercise 4-13
this uncommented solution of mine uses another string to store the reversed string
found a solution at https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_4:Exercise_13 where s[] itself is reversed
snippet kept below in commented form
The commented snippet uses the indexes of the array to reverse
*/

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100

void reverse(char s[],char t[],int pos);

void main(){

	int i,c;
	char s[MAXLENGTH],t[MAXLENGTH];
	i=0;

	while ((c=getchar())!='\n' && i<MAXLENGTH){
		s[i++]=c;
	}
	s[i]='\0';
	reverse(s,t,0);
	t[strlen(s)]='\0';

	for (i=0;i<strlen(t);i++){
		printf("%c",t[i]);
	}
}

void reverse(char s[], char t[], int pos){
	if(s[pos]!='\0'){
		reverse(s,t,pos+1);
		t[strlen(s)-1-pos]=s[pos];
	}


}


/*void reverse(char s[], int l, int r){   //reverse from l(left) to r(right) in array s
    int c;
    if (l < r) {
        reverse(s, l+1, r-1);
        c = s[l];
        s[l] = s[r];
        s[r] = c;
    }
}*/