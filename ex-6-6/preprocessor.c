/*
	k&r exercise 6-6: implement a simple version of the #define processor. getch and ungetch maybe helpful. use same routines as this section of k&r
	exception handling is not taken care of in this code
*/

#include <stdio.h>
#include <ctype.h>		//for the isspace, isalpha and isalnum routines
#include <stdlib.h>		//for the malloc and free routines
#include <string.h>

#define HASHSIZE 101	//size of hash table for this example
#define MAXWORD 100		//max size of token and replacement text in the preprocessor statement

struct nlist{
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];		//hashtable to store the preprocessor token and replacement text

int getword(char *,int max);
struct nlist *install(char *,char *);
struct nlist *lookup(char *);
unsigned hash(char *);
char *controllinesplit(char *,char *,int length);				//used to split the control line to token and replacement text

void main(int argc, char *argv[]){

	char word[MAXWORD];
	while (getword(word,MAXWORD)!=EOF){
		
		if(word[0]=='#'){/*if preprocessor control line, then first character will be #*/

			char *s,*e; //pointer start and end of words in control line. keep 2 pointers to scan through control line, one gives the start position and the other gives end position
			s=e=word;	//make both start at the beginning of the control line
			int cntr = 0; //0=#define,1=token,2=replacement text
			char *name, *defn;
			while(*e!='\0'){
				if (isspace(*e)){
					
					if(cntr==0){
						cntr++;
					}
					else if(cntr==1){
						name = (char *)malloc(e-s+1);
						controllinesplit(name,s,(e-s));
						printf("%s\n",name);
						cntr++;
					}
					else{
						defn = (char *)malloc(e-s+1);
						controllinesplit(defn,s,(e-s));
						printf("%s\n",defn);
					}

					e++;s=e;
					continue;	//skip over the e++ outside if to avoid character being missed	
				}
				e++;
			}
			install(name,defn);
		}
		else{/*found a token, check if it has a replacement text in the hash table*/
			struct nlist *np;
			np = lookup(word);
			if (np!=NULL)
				printf("The replacement text for %s in preprocessor control line is %s\n",np->name,np->defn);
			else{
				printf("token replacement text pair does not exist\n");
			}
		}
	}
}

char *controllinesplit(char *word, char *s,int length){

	char *p;
	p=word;
	while (length--){
		*p++=*s++;
	}
	*p='\0';
	return word;

}

char *str_dup(char *);			//allocates memory using malloc for the string then returns the pointer to the string, or NULL if no space left

struct nlist *install(char *name, char *defn){

	struct nlist *np;
	unsigned hashval;

	if((np=lookup(name))==NULL){	//element not found, so install it based on some criteria in the if statement

		np = (struct nlist *)malloc(sizeof(*np));
		if (np==NULL || (np->name = str_dup(name))==NULL)
			return NULL;
		hashval = hash(name);
		
		np->next = hashtab[hashval];	//null pointer as the static array is initialized as null by defauly? --> find out
		hashtab[hashval] = np;
	}
	else{							//element was found. new definition will supersede the old one
		free ((void *)np->defn);		//NEED TO FIND OUT WHY (VOID *) IS NEEDED WHEN CALLING FREE ROUTINE OF STDLIB.H HEADER
	}

	if ((np->defn = str_dup(defn))==NULL)
		return NULL;

	return np;

}

struct nlist *lookup(char *s){

	struct nlist *np;
	for ((np=hashtab[hash(s)]);np!=NULL;np=np->next){
		if(strcmp(s,np->name)==0){
			return np; /* this means that the element was found in the hash table */
		}
	}
	return NULL;	/* element not found */

}

char *str_dup(char *s){

	char *p;
	p = (char *)malloc(strlen(s)+1);
	if (p!=NULL)
		strcpy(p,s);
	return p; 
}

unsigned hash(char *s){			//routine that determines the hashvalue of the string to hash into the hash table (array)

	unsigned hashval = 0;
	while(*s!='\0'){
		hashval = *s++ * 31 + hashval;
	}
	return hashval % HASHSIZE;

}


#define BUFFSIZE 100
char buf[BUFFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);

int getword(char *word,int max){

	int c;
	char *w=word;
	while(isspace(c=getch())); 		//skip all trailing white spaces

	if (c!=EOF)
		*w++=c;

	//takes care of pre-processor control lines

	if (c=='#'){
		while(--max){
			if ((*w=getch())=='\n'){
				*++w='\0';
				return word[0];
			}
			w++;
		}
	}

	if(!isalnum(c) && c!='_'){
		*w='\0';
		return word[0];
	}

	while(--max){

		if (!isalnum(*w=getch()) && *w!='_'){
			ungetch(*w);
			break;
		}
		w++;
	}
	*w='\0';
	return word[0];
}

int getch(void){
	
	return (bufp>0) ? buf[--bufp] : getchar();
}

void ungetch(int c){

	if (bufp>=BUFFSIZE){
		printf("ungetch: too many characters\n");
	}
	else
		buf[bufp++]=c;

}