/*
sample c program to show the usage of lookup table concept
base program taken from k&r for the functions

k&r exercise 6-5: write a fucntion undef that will remove name and definition from the table maintained by lookup and install
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>			//for malloc and free routines
#include <string.h>

struct nlist{
	struct nlist *next;
	char *name;
	char *defn;
};							//struct block used in the lookup table linked list

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];		//this is the hashtable

struct nlist *install(char *, char *);
struct nlist *lookup(char *);	//install will use lookup to check if the name being installed is already present, if not will return NULL
unsigned hash(char *);			//returns the unsigned hash value of the string to hash into the array
void undef(char *);				//remove from hashtable the name and definition combination


void main(int argc, char *argv[]){

	struct nlist *p;

	p = install("name","souryadeep");

	if (p!=NULL){
		printf("%s 		%s\n",p->name,p->defn);
	}
	else{
		printf("%s\n","oops, ran out of memory...");
	}

	char *temp = "name";
	p=lookup(temp);
	printf("%s 		%s\n",(p=lookup("name"))->name,p->defn);

	/*if ((p=lookup("name"))!=NULL)
		undef("name");

	if (hashtab[hash("name")]==NULL){
		printf("%s\n","undef done");
	}*/

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

void undef(char *s) {
    struct nlist *currentPtr, *previousPtr;

    for (previousPtr = NULL, currentPtr = hashtab[hash(s)]; currentPtr != NULL; previousPtr = currentPtr, currentPtr = currentPtr->next) {

        if (strcmp(currentPtr->name, s) == 0) {
            if (previousPtr == NULL){ /* first element */
                hashtab[hash(s)] = currentPtr->next;
            }
            else /* element in the middle or at the end */
                previousPtr->next = currentPtr->next;
            /* free memory */
            free(currentPtr->name);
            free(currentPtr->defn);
            free(currentPtr);
            return;
        }
    }
}

unsigned hash(char *s){			//routine that determines the hashvalue of the string to hash into the hash table (array)

	unsigned hashval = 0;
	while(*s!='\0'){
		hashval = *s++ * 31 + hashval;
	}
	printf("%d\n",hashval);
	return hashval % HASHSIZE;

}


