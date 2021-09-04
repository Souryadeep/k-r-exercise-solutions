#include <stdio.h>
#include <string.h>

//getline is part of stdio.h header

/*
k&r exercise 5-7
taken from https://github.com/Elyasin/K-and-R-solutions/blob/master/Exercise%205-7/qsort_exercise.c
commented out below the main and readlines functions
*/

#define MAXLINES 1000 //max number of lines to be sorted

char *lineptr[MAXLINES];  //pointers to the text lines

int readlines(char *lineptr[],int nlines);		//function used to read the input lines until 1000 lines input or out of alloc space or empty string is input
void writelines(char *lineptr[],int nlines);	//function to print the lines

void qsort(char *lineptr[],int left,int right);

void main(){

	int nlines;		//number of input lines read

	if((nlines=readlines(lineptr,MAXLINES))>=0){
		qsort(lineptr,0,nlines-1);
		writelines(lineptr,nlines);
	}
	else{
		printf("error: input too big to sort\n");
	}
}

/*
void main(){
	int nlines;  //number of input lines read
    char lines[MAXLINES * MAXLEN];  //one large array for lines 

    if ((nlines = readlines(lineptr, lines, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
    } else {
        printf("error: input too big to sort\n");
}


int readlines(char *lineptr[], char lines[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];
    char *lineend = lines + MAXLINES * MAXLEN; //point to the end of lines array 

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || lines + len >= lineend)
            return -1;
        else {
            line[len - 1] = '\0'; // delete newline
            strcpy(lines, line);
            lineptr[nlines++] = lines;
            lines += len; ----------------------------------> is this allowed?
        }
    return nlines;
}


*/


#define MAXLEN 5000 //max length of 1 input line

int getline2(char *,int);  //to get the input line and also to return the length
char *alloc(int);		  //to allocate the space

int readlines(char *lineptr[],int maxlines){
	int len,nlines;
	char *p, line[MAXLEN];

	nlines = 0;

	while((len=getline2(line,MAXLEN))>1){
		if (nlines>=maxlines || (p=alloc(len)) == NULL)
			return -1;
		else{
			line[len-1] = '\0'; //remove the newlines
			strcpy(p,line);
			lineptr[nlines++]=p; 	
		}
	}
	return nlines;
}

int getline2 (char *p,int maxlength){
	int c;
	char *s=p;
	while (maxlength-- && (c=getchar())!='\n' && c!=EOF)
		*p++=c;

	if (c=='\n')
		*p++=c;

	*p='\0';

	return p-s;
}

#define ALLOCSIZE 1000000 //size of available space

static char allocbuf[ALLOCSIZE]; 	//storage for alloc
static char *allocp = allocbuf;		//next free position

char *alloc(int n){

	if(allocbuf + ALLOCSIZE - allocp >=n){
		allocp +=n;
		return allocp - n;
	}
	else 
		return 0;		//zero is not a valid address and is the only int that can be assigned to a pointer. Used interchangably with NULL which is part of stdio.h

}

void writelines(char *lineptr[],int nlines){
	while(nlines--){
		printf("%s\n",*lineptr++);  //printing each line using a pointer to that line and then incrementing to pointer in the next line
	}
}

void qsort(char *v[],int left, int right){

	int i,last;
	void swap(char *v[],int i,int j);

	if (left>=right)
		return;
	swap(v,left,(left+right)/2);

	last = left;

	for(i=left+1;i<=right;i++){
		if (strcmp(v[i],v[left])<0)
			swap(v,++last,i);
	}

	swap(v,left,last);
	qsort(v,left,last-1);
	qsort(v,last+1,right);

}

void swap(char *v[],int i, int j){

	char *temp;

	temp=v[i];
	v[i]=v[j];
	v[j]=temp;
}