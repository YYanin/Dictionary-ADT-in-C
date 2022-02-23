//Yaroslav Yanin
//1620969
//CMPS12B
//06/03/19

//Dictionary.c: rotate_left, pre_hash, and hash are taken directly from
//HashDemo.c. Some parts are also taken from the Dictionary.c(lab5)
//Implements fuctions from Dictionary.h



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include"Dictionary.h"

const int hashTSize=101; // or some prime other than 101

//--------------------------------------------------
//Taken from Dictionary.c(lab5)
typedef struct NodeObj{
   char* key;
   char* value;
   struct NodeObj* next;
} NodeObj;

// Node
typedef NodeObj* Node;

Node newNode(char* k, char* v) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->key = k;
   N->value = v;
   N->next = NULL;
   return(N);
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// StackObj
typedef struct DictionaryObj{
   Node* hashT;
   int numItems;
} StackObj;

//--------------------------------------------------

//Taken from HashDemo.c(example code)

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
   int sizeInBits = 8*sizeof(unsigned int);
   shift = shift & (sizeInBits - 1);  
   if ( shift == 0 )
      return value;
   else
      return (value << shift) | (value >> (sizeInBits - shift));
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {  
   unsigned int result = 0xBAE86554;  
   while (*input) {                   
      result ^= *input++;                
                                         
      result = rotate_left(result, 5);   
   }
   return result;  
}

// hash()
// turns a string into an int in the range 0 to hashTSize-1
int hash(char* key){
   return pre_hash(key)%hashTSize;
}

//---------------------------------------------



// newDictionary()
// constructor for the Stack type
Dictionary newDictionary(void){
   Dictionary D = malloc(sizeof(StackObj));
   assert(D!=NULL);
   D->hashT = calloc(hashTSize, sizeof(Node));
   D->numItems = 0;
   return D;
}

// freeDictionary()
// destructor for the Dictionary type
void freeDictionary(Dictionary* pD){
	if( pD!=NULL && *pD!=NULL ){
		if( !isEmpty(*pD) ){
			makeEmpty(*pD);
		}
		free((*pD)->hashT);
		free(*pD);
		*pD = NULL;
	}
}

// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D){
   if( D==NULL ){
      fprintf(stderr, 
              "Dictionary Error: calling isEmpty() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return(D->numItems==0);
}

//Copied isEmpty function and replaced the return variable
int size(Dictionary D){
	if( D==NULL ){
      fprintf(stderr, 
              "Dictionary Error: calling size() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return D->numItems;
}

//Translated into C. Taken from pa3
Node findKey(Dictionary D, char* key){
	Node x=D->hashT[hash(key)];
	if(x!=NULL){
		for(int y = 1; y<=D->numItems; y++){
			if(strcmp(x->key, key) != 0){
				
				x = x->next;
			} else{
				return x;
			}
		}
	}
	return NULL;
}

char* lookup(Dictionary D, char* k){
	for(Node x = D->hashT[hash(k)]; x!=NULL; x=x->next){
		if(strcmp(x->key, k) ==0){
			return x->value;
		}
	}
	return NULL;
}

void insert(Dictionary D, char* k, char* v){
	
	Node x = newNode(k,v);
	int key = hash(k);
	if(lookup(D,k)==NULL){
		if(D->hashT[key] != NULL){
			
			x->next = D->hashT[key];
			
			D->hashT[key]=x;
			D->numItems++;
		} else{
			D->hashT[key]=x;
			D->numItems++;
		}
	} else{
		fprintf(stderr, "Error:duplicate key");
		exit(EXIT_FAILURE);
	}
}

void delete(Dictionary D, char* k){
	
	if(lookup(D,k) == NULL){
		fprintf(stderr, "Error: deleting non-existant \n");
		exit(EXIT_FAILURE);
	} else{
		int key = hash(k);
		Node x = D->hashT[key];
		if(strcmp(x->key, k) != 0){
			Node p = x;
			Node t= x->next;

			while(t->key != k){
				t=t->next;
				p=p->next;
			}

			p->next=t->next;
			t->next=NULL;
			freeNode(&t);
			D->numItems--;
		} else{
			D->hashT[key]= x->next;
			x->next = NULL;
			freeNode(&x);
			D->numItems--;
		}
	}
}

void makeEmpty(Dictionary D){
	for(int x = 0; x<hashTSize; x++){
		while(D->hashT[x]!=NULL){
			Node y;
			y=D->hashT[x];
			D->hashT[x]=y->next;
			freeNode(&y);
			y=NULL;
		}
	}D->numItems = 0;
}

void printDictionary(FILE* out, Dictionary D){
	for(int j = 0;j<hashTSize ;j++ ){
		Node x= D->hashT[j];
		while(x!=NULL){
			fprintf(out,"%s %s\n", x->key, x->value);
			x=x->next;
		}
	}
}

//////////////////////////////////////////////////////////////


