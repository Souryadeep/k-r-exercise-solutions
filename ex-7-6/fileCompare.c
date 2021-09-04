/*
k&r exercise 7-6: write a program to compare two files, printing the first line where they differ
this solution assumes that both files have equal number of lines
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>			//exit() is defined in the stdlib header

#define MAXLENGTH 200		//max of 200 char per line

void fileCompare(FILE *,FILE *);	//function used to compare the files line by line. we will make use of the strcmp function from string.h for the comparison
int get_line(char *line,int max,FILE *);

void main(int argc, char *argv[]){

	FILE *fp1, *fp2;	//two files that are from std input

	if (argc == 1){
		printf("fileCompare.c: Requires the 2 file names to be input for compare. Usage: fileCompare <file1> <file2>\n");
		exit(1);
	}else{
		if((fp1=fopen(*++argv,"r"))==NULL || (fp2=fopen(*++argv,"r"))==NULL){
			printf("%s\n","Unable to open file, please check both input file names and ensure they exist");
			exit(2);
		}else{
			fileCompare(fp1,fp2);
			fclose(fp1);fclose(fp2);
		}
	}
	exit(0);
}

void fileCompare(FILE *fp1,FILE *fp2){

	char lineF1[MAXLENGTH], lineF2[MAXLENGTH]; 
	while(get_line(lineF1,MAXLENGTH,fp1) && get_line(lineF2,MAXLENGTH,fp2)){//get_line return 0 when the next line is empty and means EOF
		if(strcmp(lineF1,lineF2)!=0){
			printf("The lines for the two files differ at the corresponding line number:\n %s \n %s",lineF1,lineF2);
			exit(3);
		}
	}
	printf("%s\n","Files do not differ at any line");

}

int get_line(char *line,int max,FILE *fp){

	if(fgets(line,max,fp)==NULL)		//using the fgets function to get a line inluding the '\n' and terminated by '\0'
		return 0;
	else
		return strlen(line);

}

