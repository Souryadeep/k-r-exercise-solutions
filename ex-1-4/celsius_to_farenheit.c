/*
k&r exercise 1-4: write a program to print the corresponding celsius to farenheit table
*/

#include <stdio.h>

#define LOWER 0			/*lower limit of table. this is a symbolic constant in C, does not need to be terminated by ;*/
#define UPPER 300
#define STEP 20

float celsius_to_farenheit(int fahr); //this is the function prototype as required in C

void main(){
	
	float fahr, celsius;
	int c;

	//c = getchar();
	//printf("%s\n",EOF);

	fahr=UPPER;
	printf("Farenheit\tCelsius\n");
	while(fahr >= LOWER){
		celsius = celsius_to_farenheit(fahr);
		printf("%3.0f\t\t%6.1f\n",fahr,celsius);
		fahr = fahr - STEP;
	}
}

float celsius_to_farenheit(int fahr){ //function definition
	return (5.0/9.0)*(fahr-32);
}