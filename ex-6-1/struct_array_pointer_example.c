/*
This program is to count C keywords

k&r exercise 6-1: modify getword to handle underscores, string constants, comments, pre-precessor control lines
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct key{
	char *word;
	int count;
}keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "define", 0,
    "default", 0,
    "do", 0,
    "double", 0,
    "else", 0,
    "enum", 0,
    "extern", 0,
    "float", 0,
    "for", 0,
    "goto", 0,
    "if", 0,
    "int", 0,
    "long", 0,
    "register", 0,
    "return", 0,
    "short", 0,
    "signed", 0,
    "sizeof", 0,
    "static", 0,
    "struct", 0,
    "switch", 0,
    "typedef", 0,
    "union", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};  //initialise the keyword array of structueres externally when defined since it contains a constant set of names

#define MAXWORD 100
#define NKEYS (sizeof(keytab)/sizeof(struct key)) //this is the size of the keytab array and decided at compile tim itself

int getword(char *, int);
struct key *binsearch(char *, struct key *,int);

void main(){

	char word [MAXWORD];
	struct key *p;

	while(getword(word,MAXWORD) != '1'){// next line is used in this program to terminate the search for the keywords
		if (isalpha(word[0])){
			if((p=binsearch(word,keytab,NKEYS))!=NULL){
				p->count++;
			}
		}

	}

	for(p=keytab;p<keytab+NKEYS;p++){
		if(p->count>0)
			printf("%4d  %s\n",p->count, p->word);
	}
}

struct key *binsearch(char *word, struct key *tab,int n){

	int cond;

	struct key *high = &tab[n]; //tab[n] is allowed in c programming and not out of range. First element beyond the end of the array will work correctly with pointer arithmetic
	struct key *low = &tab[0];
	struct key *mid;

	while(low<=high){
		mid= low + (high-low)/2; //subtraction is legal in pointer arithemetic, but not addition

		if ((cond = strcmp(word,mid->word))<0)
			high = mid;
		else if (cond > 0)
			low = mid+1;
		else
			return mid;
	}
	return NULL;
}

#define BUFFSIZE 100   //max buffer size
char buffer[BUFFSIZE]; //buffer used to store the additional characters scanned
int bufp = 0;

int getch(void);
void ungetch(int);

int getword(char *word,int max){ //routine to get the word from input to compare to see if it is a keyword

	int c;
	char *w = word;

	while(isspace(c=getch()));

	if (c!=EOF)
		*w++=c;


	//takes care of pre-processor control lines

	if (c=='#'){
		while(--max){
			if ((*w=getch())=='\n'){
				*++w='\0';
				return word[0];
			}
		}
	}

	//takes care of comments, single line and multi-line

	if (c == '/'){
		c=getch();
		if (c=='/'){
			while(--max){
				if ((*w=getch())=='\n'){
					*++w='\0'; 				//increment before assigning
					return word[0];
				}
				w++;
			}
		}
		else if(c=='*'){
			while(--max){
				if ((*w=getch())=='/'){
					if (*(w-1)=='*'){
						*++w='\0';
						return word[0];
					}
				}
				w++;
			}
		}
		else{				//this would neither be a single or multi-line comment
			ungetch(c);
			*w='\0';
			return '/';
		}
	}

	//takes care of string constants

	if (c == '\"'){
		while(--max){
			if ((*w=getch())=='\"'){
				*++w='\0';
				return word[0];
			}
		}
	}


	//takes care of underscores
	if (!isalpha(c) && c!='_'){
		*w='\0';
		return c;
	}

	while (--max){//max is the max number of char a word can have as per the program
		if(!isalnum((*w=getch())) && *w!='_'){
			ungetch(*w);
			break;
		}
		w++;
	}
	*w='\0';
	return word[0];
}

int getch(void){

	return (bufp>0)?buffer[--bufp] : getchar();
}

void ungetch(int c){

	if (bufp>=BUFFSIZE)
		printf("ungetch: too many characters\n");
	else{
		buffer[bufp++] = c;
	}
}
