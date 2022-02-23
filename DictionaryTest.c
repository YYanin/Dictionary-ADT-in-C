//Yaroslav Yanin
//1620969
//CMPS12B
//06/03/19

//DictionaryTest: tests fucntions in Dictionary.c




#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"Dictionary.h"

int main(int argc, char* argv[]){


  Dictionary Dic = newDictionary();

  //Testing isEmpty
  printf("Testing isEmpty: \n");
  if(isEmpty(Dic) == 1){
  	printf("Passed \n");
  } else{
  	printf("Failed \n");
  }

  //Testing insert
  char* one[] = {"one", "two", "three", "four"};
  char* two[] = {"one1", "two2", "three3", "four4"};

  printf("Testing insert: \n");
  for(int i = 0; i<4; i++){
  	insert(Dic, one[i], two[i]);
  }

  if(isEmpty(Dic) == 0){
  	printf("Passed \n");
  } else{
  	printf("Failed \n");
  }

  //Testing size
  printf("Testing size: \n");
  if(size(Dic) == 4){
  	printf("Passed \n");
  } else{
  	printf("Failed \n");
  }
  
  //Testing lookup
  printf("Testing lookup: \n");
  if(lookup(Dic, one[1])==two[1]){
  	printf("Passed \n");
  }else{
  	printf("Failed \n");
  }

  printf("Testing printDictionary: \n");

  //Testing printDictionary
  printDictionary(stdout, Dic);

  //Testing delete
  printf("Testing delete: \n");
  delete(Dic, "one");

  if(size(Dic) == 3){
  	printf("Passed \n");
  } else{
  	printf("Failed \n");
  }

  //Testing makeEmpty
  printf("Testing makeEmpty: \n");
  makeEmpty(Dic);
  if(isEmpty(Dic) == 1){
  	printf("Passed \n");
  } else{
  	printf("Failed \n");
  }

  freeDictionary(&Dic);
  
  return (EXIT_SUCCESS);
    
}
