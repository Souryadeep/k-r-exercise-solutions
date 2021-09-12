/*
 	k&r exercise 1-6 solution: Verify that expression getchar()!=EOF is 0 or 1
 */

#include <stdio.h>

void main(){
	int res,c;   //res will hold the value evaluated by != expression
	res = (getchar()!=EOF);

	printf("The value of getchar()!=EOF is %d\n",res);
}
