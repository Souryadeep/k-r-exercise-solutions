//k&r exercise 4-14: define a macro swap (t,x,y) where t is the type of argument x and y

#include <stdio.h>

#define swap(t,x,y) {\
	t tmp;\
	tmp = x; x = y; y = tmp;\
}

void main(){

	int x,y;
	x=5,y=2;

	printf("%d\t%d\n",x,y);
	swap(int,x,y); //this is not a function call but is using a macro: saves function call time overhead
	printf("%d\t%d\n",x,y);

}