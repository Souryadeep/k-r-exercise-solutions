/*
k&r exercise 6-2:
print all words from a doc (in this case take as input to the program) and for each word print the line number where it occurred
need a binary search routine, and if the word entered is from the noise list then dont add to tree and count it
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
define symbolic constants and varaibles with global scope here
*/

#define MAXLINES 100 		//max input lines to be accepted by this program is 100
#define MAXWORD 100			//max word size in input

char *noise[]={"a", "an", "and", "are", "at", "be", "by", "can", "did", "do", "done", 
    "for", "from", "have", "he", "her", "his", "if", "in", "into", "is", "it", 
    "its", "many", "must", "no", "none", "not", "of", "off", "on", "or",  
    "our", "ours", "so", "such", "that", "the", "them", "they", "their", 
    "this", "to", "too", "us", "was", "we", "were", "what", "who", "with", 
    "without"};			// create a pointer array of type char. something like a 2 dimenionsal array that is holding pointers to string literals/char arrays

//#define NLENGTH 52		//number of noise words
#define NLENGTH (sizeof noise / sizeof (char*))

/*
define the structure here
*/

struct tnode {
	char *word;
	int count;
	int lineNumber[MAXLINES];	//referencing this array with pointer seems to be problematic when using with a pointer to this structure
	int lncount;
	struct tnode *left;
	struct tnode *right;
};

/*
declare functions here
*/

struct tnode *addtree(struct tnode *, char *,int);
int getword(char *,int);
void treeprint(struct tnode *);
int binsearch(char *noise[],char *,int);

void main(int argc, char *argv[]){

	printf("%d\n",NLENGTH);

	int line = 1;
	char word[MAXWORD];
	int cond;	//flag to identify whether the word is a noise word or not

	struct tnode *root = NULL; //pointer to root initialised to be a NULL

	while (line<MAXLINES && getword(word,MAXWORD)!='1'){
		if (word[0]=='\n'){
			printf("newline encountered\n");
			line++;
		}
		if (word[0]!='\n'){
			//printf("exp\n");				//for some reason this print is required otherwise code is unexpectedly exiting when \n is encountered
			if(isalpha(word[0]) && (cond=binsearch(noise,word,NLENGTH))==-1){
				//printf("%s\n",word);
				root = addtree(root,word,line);
			}
		}
	}
	treeprint(root);
}

/*
routine to add child node to the tree
uses talloc to assign space and strdup to assign the word to the tnode structure
*/

#include <stdlib.h>

struct tnode *talloc(void);
char *strdup_(char *);

struct tnode *addtree(struct tnode *p,char *w,int line){

	/*
		check whether the word is a noise word using binary search
	*/

	int cond;

	if (p==NULL){
		p=talloc();
		p->word = strdup_(w);
		p->count = 1;
		p->lineNumber[p->lncount++]=line;
		p->left = p->right = NULL;
	}
	else if((cond=strcmp(w,p->word))==0){
		p->count++;
		p->lineNumber[p->lncount++]=line;
	}
	else if (cond<1){
		p->left = addtree(p->left,w,line);
	}
	else{
		p->right = addtree(p->right,w,line);
	}

	return p;

}

struct tnode *talloc(void){
	return (struct tnode *)malloc(sizeof(struct tnode));
}

char *strdup_(char *s){
	char *p;
	p = (char *)malloc(strlen(s)+1);	//+1 to accomodate for the '\0'
	if (p!=NULL)
		strcpy(p,s);
	return p;
}

/*
routine to print the words with the list of lines it occured in
*/
void treeprint(struct tnode *p){

	if (p!=NULL){
		treeprint (p->left);
		printf("Count of word:%4d   word:%s\tlinenumbers: ",p->count,p->word);
		int i=0;
		while(i<p->lncount){
			printf("%d\t", p->lineNumber[i++]);
		}
		printf("\n");
		treeprint(p->right);
	}
}

/*
binary search routine to check if the word is a noise word
*/

int binsearch(char *noise[],char *word, int n){

	int cond;
	int low,high,mid;
	low=0;
	high = n-1;

	//printf("%s\n",word);	//---> why do i need this print here for code to work???

	while(low<=high){

		mid = (low+high)/2;
		if ((cond = strcmp(word,noise[mid]))<0){
			high = mid-1;
		}
		else if (cond>0){
			low=mid+1;
		}
		else{
			return mid;
		}
	}
	return -1;
}


/*
routine used to getword using getch and ungetch functions
modification made to take care of the next line to increment the line counter
*/

#define BUFFSIZE 100   //max buffer size
char buffer[BUFFSIZE]; //buffer used to store the additional characters scanned
int bufp = 0;

int getch(void);
void ungetch(int);


int getword(char *word,int max){

	//printf("here\n");

	char *w=word;
	int c;

	while (isspace(c=getch()) && c!='\n');		//skip over white spaces

	if (c!=EOF)
		*w++=c;
	
	//process non comment, non sting literal, non preprocessor control lines

	if (isalpha(c) || c=='_'){

		while((isalnum(c=getch()) || c=='_') && max--){
			*w++=c;
		}
		ungetch(c);		//place in buffer the extra read character
		*w='\0';
		return word[0];
	}
	else{
		*w='\0';
		return word[0];
	}

}


int getch(void){

	return (bufp>0) ? buffer[--bufp] : getchar();

}

void ungetch(int c){

	if (bufp>=BUFFSIZE){
		printf("ungetch: too many characters\n");
	}
	else{
		buffer[bufp++]=c;
	}

}