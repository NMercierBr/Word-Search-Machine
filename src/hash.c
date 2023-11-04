#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h" // global functions declarations

// ------------------------------------------------------------------------
// inner functions declarations
// ------------------------------------------------------------------------

// TO BE COMPLETED

//------------------------------------------------------------------------
// global functions definitions
//------------------------------------------------------------------------

// compute hash value for word
// returns : N ; 0 <= N < size
int hashcode(char word[], int size)
{
	int hash_val = 0;
	while( *word != '\0' )
	hash_val += *word++;
	return( hash_val % size );
}

/**
   create and initialize hash table

   returns : pointer to table or NULL if creation error
*/
hash_table * create_table()
{
  hash_table * htable_ptr = (hash_table*) malloc(sizeof(hash_table));
  htable_ptr->hsize = MAX_ENTRIES;
  htable_ptr->htable = (word_list*) malloc(sizeof(word_list) * htable_ptr->hsize );
  for(int i = 0; i < htable_ptr->hsize ; i++ ){
	htable_ptr->htable[i].first_word = NULL;
	htable_ptr->htable[i].last_word = NULL;
   }
  return htable_ptr;
}

/**
   search a word in table ; print word if found, with number of occurrences
   and file where word is found

   parameters :
   word : the word to look for
   filelist   : pointer to table of files
   htable_ptr : pointer to hash table

   returns : true if found, false otherwise
*/
int search_word(char word[], listfile_entry * filelist, hash_table * htable_ptr)
{
   int indexHash = hashcode(word,htable_ptr->hsize);
	int booleen = 0;
	word_list * word_ptr = htable_ptr-> htable;
	word_entry * ptr = word_ptr[indexHash].first_word;
	while(ptr!=NULL) {
		if(strcmp(word, ptr->word) == 0) {
			booleen = 1;
			printf("The word %s appears %d times in the file %s\n",word,ptr->times, filelist[ptr->in_file].filename);
		}
		ptr = ptr->next;
 	}
   if(booleen == 0){
      printf("The word %s is not contained in any files\n", word);
   }
  return booleen;
}

/**
   lookup for word in table and update table accordingly

   parameters :
   htable_ptr : pointer to hash table
   word : word to be added into the hash table
   filename   : filename from where the word was read
   file_index:  the position where the filename has been stored
*/
//Si mise a jour dans filelist, hashtable mise a jour egalement

void update_table(hash_table * htable_ptr, char word[], char filename[],int file_index)
{
    int indexHash = hashcode(word, htable_ptr->hsize);
    word_list *word_ptr = &(htable_ptr->htable[indexHash]);
    word_entry *ptr = word_ptr->first_word;
    
    while (ptr != NULL) {
        if (strcmp(word, ptr->word) == 0 && file_index == ptr->in_file) {
            ptr->times += 1;
            return;
        }
        ptr = ptr->next;
    }

    word_entry *nvlelem = (word_entry*)malloc(sizeof(word_entry));
    if (nvlelem == NULL) {
        perror("Allocation error");
        exit(-2);
    }
    strcpy(nvlelem->word, word);
    nvlelem->times = 1;
    nvlelem->in_file = file_index;  
    nvlelem->next = NULL;

    if (word_ptr->first_word == NULL) {
        word_ptr->first_word = nvlelem;
        word_ptr->last_word = nvlelem;
    } else {
        word_ptr->last_word->next = nvlelem;
        word_ptr->last_word = nvlelem;
    }
   
}


/**
   print table contents

   parameters :
   htable_ptr : pointer to hash table
   filelist   : pointer to table of files
*/
void print_table(hash_table * htable_ptr, listfile_entry * filelist)
{
   word_list * word_ptr = htable_ptr-> htable;
   int i = 0;
   word_entry * ptr = word_ptr[i].first_word;
  while (i<MAX_ENTRIES)
  {
   ptr = word_ptr[i].first_word;
    while (ptr !=  NULL){
      printf("Word : %s , file :  %s , NbOccurences : %d.\n",ptr->word, filelist[ptr->in_file].filename ,ptr->times);
      ptr=ptr->next;
   }
   i++;
  }
}


/**
   free hash table

   parameters :
   htable_ptr : pointer to hash table
*/
void free_table(hash_table *htable_ptr) {
    if (htable_ptr != NULL) {
        if (htable_ptr->htable != NULL) {
            for (int i = 0; i < MAX_ENTRIES ; i++) {
                word_entry * current = htable_ptr->htable[i].first_word;
                while (current != NULL) {
                    word_entry *temp = current;
                    current = current->next;
                    free(temp);
                }
            }
            free(htable_ptr->htable);
        }
        free(htable_ptr);
    }
}
