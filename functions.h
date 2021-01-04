#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORDLENGTH 46
#define NOALPHABETS 26
/*
 *   File name: functions.h
 *   Author: Rehan Nagoor Mohideen
 *   Student ID: 1100592
 *   Summary: This header file contains all the funcitons for Assignment 1 for the alphabetical_printing.c program.
 *   Every functions summary is displayed above the function.
 */

/*This function computes the file sie (in bytes) of an opened file*/
int file_size(FILE *fp)
{
  int sz = 0;
  fseek(fp, 0L, SEEK_END);
  sz = ftell(fp);
  rewind(fp);
  return sz;
}

/*This funciton reads in words from the file and stores it in a 2D malloced array*/
char **read_words(FILE *fp){
  int i,j;
  int k=0;
  int maxWords = file_size(fp)/2;
  char word[MAXWORDLENGTH];
  char **sptr;

/* creating and mallocing 2D array*/
  sptr = malloc(sizeof(char *) * maxWords);
  if (sptr == NULL) {/*for error handling*/
    printf("error: not enough space for malloc\n");
    exit(1);
  }

  for (i = 0; i < maxWords; i++) {
    sptr[i] = malloc(sizeof(char) * MAXWORDLENGTH);
    if (sptr[i] == NULL) {/*for error handling*/
      printf("error: not enough space for malloc\n");
      for (j = 0; j < i; j++) {/*to free previously malloced space during an error*/
        free(sptr[j]);
      }
      free(sptr);
      exit(1);
    }
  }

/*Takes words from files and stores them*/
  i=0;
    while (fscanf(fp, "%s", word)!= EOF) {
      if ((word[0]>64 && word[0]<91) ||(word[0]>96 && word[0]<123)) { /*Checks if character are alphabets*/
        /*sptr[i++] = malloc(sizeof(char) * MAXWORDLENGTH);*/
        strcpy(sptr[k], word);
        k++;
      }
    }
  /*sptr[i] = malloc(sizeof(char) * MAXWORDLENGTH);*/
  sptr[k] = NULL;
  return sptr;
}


/*This funciton is used to print out all words in an array using the pointer to the start of the malloc array*/
void print_words(char **sptr){
  int i;

  for (i = 0; sptr[i] != NULL; i++) {
    printf("%s\n", sptr[i]);
  }
}


/*This function takes in the pointer to the array of words and counts how many words begin with each letter
of the alphabet and stores it in another 1D array of length 26*/
int *alphabetical_word_count(char **sptr) {
  int *alphabeticalWC;
  int i,j;

  alphabeticalWC = malloc(sizeof(int)*NOALPHABETS);/*creating the array using malloc*/
  for (i = 0; i < NOALPHABETS; i++) {
    alphabeticalWC[i]=0;
  }

  for (j = 0; j < NOALPHABETS; j++) {/*for each letter*/
  for (i = 0; sptr[i] != NULL; i++) {/*goes through the array and takes the particualar words for that letter*/
    /*compare the first letter of the word to be the required letter using ascii*/
    if (sptr[i][0]== 'a'+j || sptr[i][0]== 'A'+j) {
      alphabeticalWC[j]++;
    }
  }
  }

  return alphabeticalWC;
}


/*This function is used to print out the number of words that start with each letter*/
void print_alphabetical_word_count(int *alphabeticalWC){
  int i;
  char letter = 'a';

  for (i = 0; i<NOALPHABETS ; i++) {
    printf("%c = %d\n", letter++, alphabeticalWC[i]);
  }
}


/*This function creates a 3D array where all the words from the original array are stored alphabetically using
the pointer of the original array and the pointer to the array of alphabetical word count*/
char ***create_alphabetical_array(char **sptr, int *alphabeticalWC){
  char ***alphabetical_array;
  int i, j, k, k1;
  int noWordsCopied = 0;

/*creating the three dimentional array*/
  alphabetical_array = malloc(sizeof(char **) * NOALPHABETS);
  if (alphabetical_array == NULL) {/*for error handling*/
    printf("error: not enough space for malloc\n");
    exit(1);
  }

  for (i = 0; i < NOALPHABETS; i++) {
    alphabetical_array[i] = malloc(sizeof(char*) * (alphabeticalWC[i] +1));/*mallocing the 2d dimension of the array*/
    /*for error handling*/
    if (alphabetical_array[i] == NULL) {
      printf("error: not enough space for malloc\n");
      for (k = 0; k < i; k++) {
        free(alphabetical_array[k]);
      }
      free(alphabetical_array);
      exit(1);
    }

    for (j = 0; j < (alphabeticalWC[i] +1); j++) {
      alphabetical_array[i][j] = malloc(sizeof(char) * MAXWORDLENGTH);/*mallocing the 3rd dimension of the array*/
      /*error handling*/
      if (alphabetical_array[i][j] == NULL) {
        printf("error: not enough space for malloc\n");
        for (k = 0; k < i+1; k++) {
          for (k1 = 0; k1 < j; k1++) {
            free(alphabetical_array[k][k1]);
          }
          free(alphabetical_array[k]);
        }
        free(alphabetical_array);
        exit(1);
      }
    }
  }

/*storing the words alphabetically*/
  for (i = 0; i < NOALPHABETS; i++) {
    for (j = 0; noWordsCopied < (alphabeticalWC[i]+1) && sptr[j] != NULL; j++) {
      /*to check the first letter of the corresponds to the array element letter and stores accordingly*/
      if (sptr[j][0] == 'a'+i || sptr[j][0] == 'A'+i) {
        strcpy(alphabetical_array[i][noWordsCopied], sptr[j]);
        noWordsCopied++;
      }
    }
    alphabetical_array[i][noWordsCopied]=NULL;
    noWordsCopied=0;
  }

  return alphabetical_array;
}


/*this function is to free up the space used by the malloc for the alphabetic array when the array
is not needed anymore*/
void free_alphabetical_array(char ***alphabetical_array){
  int i,j;

  for (i = 0; i < NOALPHABETS; i++) {
    for (j = 0; j < (sizeof(alphabetical_array[i]) / (MAXWORDLENGTH * sizeof(char)) ); j++) {
      free(alphabetical_array[i][j]);
      alphabetical_array[i][j]=NULL;
    }
    free(alphabetical_array[i]);
    alphabetical_array[i]=NULL;
  }
  free(alphabetical_array);
  alphabetical_array=NULL;
}


/*This function is to print out all the words alphabetically using the pointer to the atart of the alphabetical array*/
void print_words_alphabetically(char ***alphabetical_array){
  int i;
  for (i = 0; i < NOALPHABETS; i++) {
    printf("'%c'\n",'A'+i);
    if (alphabetical_array[i][0]==NULL) {
      printf("There are no words that begin with the letter '%c'\n", 'A'+i);
    }else {
      print_words(alphabetical_array[i]);/*uses the print words funciton to print the elements*/
    }
    printf("\n");
  }
}
