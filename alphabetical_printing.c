#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

/*
 *   Program name: alphabetical_printing.c
 *   Author: Rehan Nagoor Mohideen
 *   Student ID: 1100592
 *   Summary: This program takes 2 files of words and prints the words out in the original order,
 *   prints out the number of words for each alphabet and then prints out all the words alphabetically.
 *   This program contains the main funciton for the other functions to occur and the program to run.
 */

int main ( int argc, char *argv[] ) {
  FILE *fp;
  char **sptr;
  int *alphabeticalWC;
  char ***alphabeticalArray;
  int j;

  if ( (fp = fopen("a1_words.txt", "r")) != NULL ) {/*checks to make sure the fist file exists and opened properly*/
    /*in order to print out the words in the file in the original order*/
    sptr = read_words(fp);
    print_words(sptr);
    printf("\n");
    /*To print out the number of words that start with the respectic alphabets*/
    alphabeticalWC = alphabetical_word_count(read_words(fp));
    print_alphabetical_word_count(alphabeticalWC);
    printf("\n");
    /*To print out the words alphabetically*/
    alphabeticalArray = create_alphabetical_array(sptr,alphabeticalWC);
    print_words_alphabetically(alphabeticalArray);
    printf("\n");
    /*To free up the space used in the malloc for alphabetical array*/
    free_alphabetical_array(alphabeticalArray);
  } else {/*if the file cannot be opened*/
    printf ( "Cannot open a1_words.txt\n");
    return ( -1 );
  }
  /*To free up the other arrays used*/
  for (j = 0; j < file_size(fp)/2; j++) {
    free(sptr[j]);
    sptr[j]=NULL;
  }
  free(sptr);
  sptr = NULL;
  free(alphabeticalWC);
  alphabeticalWC = NULL;



  if ( (fp = fopen("a1_moreWords.txt", "r")) != NULL ) {/*checks to make sure the second file exists and opened properly*/
    /*in order to print out the words in the file in the original order*/
    sptr = read_words(fp);
    print_words(sptr);
    printf("\n");
    /*To print out the number of words that start with the respectic alphabets*/
    alphabeticalWC = alphabetical_word_count(read_words(fp));
    print_alphabetical_word_count(alphabeticalWC);
    printf("\n");
    /*To print out the words alphabetically*/
    alphabeticalArray = create_alphabetical_array(sptr,alphabeticalWC);
    print_words_alphabetically(alphabeticalArray);
    /*To free up the space used in the malloc for alphabetical array*/
    free_alphabetical_array(alphabeticalArray);
  } else {/*if the file cannot be opened*/
    printf ( "Cannot open a1_moreWords.txt\n");
    return ( -1 );
  }
  /*To free up the other arrays used*/
  for (j = 0; j < file_size(fp)/2; j++) {
    free(sptr[j]);
    sptr[j]=NULL;
  }
  free(sptr);
  sptr = NULL;
  free(alphabeticalWC);
  alphabeticalWC = NULL;


  return 0;
}
