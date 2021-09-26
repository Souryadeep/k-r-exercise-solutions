/*
sample program of a self referential structure: binary tree
used for counting the occurence of words in a sentence
this sample does not take into account an imbalanced tree, where the computation time would be a worst case scenario
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAXWORD 100 //max length of a word

struct tnode {			//self referential structure tnode that is used as a node of the tree
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;		//legal since left and right are pointers to a struct of type tnode and not tnode itself. struct is not allowed to contain an instance of itself
};

int getword(char *, int); //routine used to get word from the input sequence from cmd line
struct tnode *addtree(struct tnode *,char *);//function that adds node to tree and returns a pointer to that structure
void treeprint(struct tnode *); //only send a pointer to the root node, rest is taken care by the function

void main(){

	char word[MAXWORD];
	struct tnode *root;

	root = NULL;
	while (getword(word,MAXWORD)!='1'){

		if (isalpha(word[0])){
			root = addtree(root,word);
		}
	}
	treeprint(root);
}

#include <stdlib.h>

struct tnode *talloc(void);
char *strdup_(char *);

struct tnode *addtree(struct tnode *p, char *w){	//now binary search is not being performed, but the binary tree kind of evaluates to what binsearch was doing. **Not in the worst case scenario as mentioned in comments above**

	int cond;

	if (p==NULL){
		p=talloc();
		p->word = strdup_(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if ((cond=strcmp(w,p->word))==0){
		p->count++;
	}
	else if (cond<0){
		p->left = addtree(p->left,w);
	}
	else{
		p->right = addtree(p->right,w);
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

void treeprint(struct tnode *p){

	if (p!=NULL){
		treeprint(p->left);
		printf("%4d   %s\n",p->count,p->word);
		treeprint(p->right);
	}

}

//getch and ungetch routines for getword routine that is called from main

#define BUFFSIZE 100   //max buffer size
char buffer[BUFFSIZE]; //buffer used to store the additional characters scanned
int bufp = 0;

int getch(void);
void ungetch(int);

int getword(char *word, int max){

	int c;
	char *w=word;

	while(isspace(c=getch())); //skip over white spaces

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

	if (!isalpha(c) && c!='_'){
		*w='\0';
		return word[0];
	}

	while (--max){	//-- is prefix becuase one character is already filled prior to this loop, above
		if(!isalnum(*w=getch()) && *w!='_'){
			ungetch(*w);
			break;
		}
		w++;
	}
	*w='\0';
	return word[0];

}

int getch(void){

	return (bufp>0)?buffer[--bufp]:getchar();

}

void ungetch(int c){

	if (bufp>=BUFFSIZE){
		printf("ungetch: too many characters\n");
	}
	else{
		buffer[bufp++]=c;
	}

}