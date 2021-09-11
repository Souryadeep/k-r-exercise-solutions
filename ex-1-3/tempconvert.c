/*
k&r exercise 1-3: modify the temperature conversion program to print a heading above the table
*/

#include <stdio.h>

float farenheit_to_celsius(float farenheit); //this is the function prototype as required in C

void main(){
	
	float fahr, celsius;
	int lower, upper, step;
	
	lower = 0;
	upper = 300;
	step = 20;

	fahr=lower;
	printf("Farenheit\tCelsius\n");
	while(fahr <= upper){
		celsius = farenheit_to_celsius(fahr);
		printf("%3.0f\t\t%6.1f\n",fahr,celsius);
		fahr = fahr + step;
	}
}

float farenheit_to_celsius(float fahr){ //function definition
	return (5.0/9.0)*(fahr-32);
}
