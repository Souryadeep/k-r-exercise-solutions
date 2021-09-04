/*
k&r exercise 5-8
add in error handling for day_of_year function
*/

#include <stdio.h>

static char daytab[2][13] = {{0,31,28,31,30,31,30,31,31,30,31,30,31},{0,31,29,31,30,31,30,31,31,30,31,30,31}};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pda);

void main(){

	int month, day, year, result;

	month = 4, year = 1988, day = 15; // initialise to some value to test code

	result = day_of_year(year,month,day);
	printf("Year %d, Month %d, Day %d is Day #%d of the year\n",year,month,day,result);

	month_day(1988,result,&month,&day);
	printf("This day of this year is the %d day of month# %d\n", day, month);

}

int day_of_year(int year, int month, int day){

	int i,leap;

	leap = year%4==0 && year%100!=0 || year%400 == 0;

	if (month<1 || month>12)
		return -1;
	else{
		if (day<1 || day>daytab[leap][month])
			return -1; 
	}

	for (i=1;i<month;i++){
		day += daytab[leap][i];
	}
	return day;

}

void month_day(int year, int yearday, int *pmonth, int *pda){

	int i,leap;
	leap = year%4==0 && year%100!=0 || year%400 == 0;

	for (i=1;yearday>daytab[leap][i];i++){
		yearday-=daytab[leap][i];
	}
	*pmonth = i;
	*pda = yearday;


}