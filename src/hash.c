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
   int indexHash = hashcode(word,strlen(word));
	int booleen = 0;
	word_list * word_ptr = htable_ptr-> htable;
	word_entry * ptr = word_ptr[indexHash].first_word;
	while(ptr!=NULL) {
		if(ptr->word == word) {
			booleen = 1;
			printf("Le mot %s apparait %d fois dans le fichier %s",word,ptr->times, filelist[indexHash].filename);
		}
		ptr = ptr->next;
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
   int indexHash = hashcode(word,strlen(word));
   word_list * word_ptr = htable_ptr-> htable;
	word_entry * ptr = word_ptr[indexHash].first_word;
   while(ptr!=NULL){
      if(word == ptr->word && file_index == ptr->in_file) {
         ptr->times += 1;
         exit(0);
      }
      ptr = ptr->next;
   }
   word_entry * nvlelem = (word_entry*) malloc(sizeof(word_entry));
   strcpy(nvlelem->word, word);
   nvlelem->times = 1;
   nvlelem->in_file = file_index;

   ptr->next = nvlelem;
   word_ptr[indexHash].last_word = nvlelem;
}

/**
   print table contents

   parameters :
   htable_ptr : pointer to hash table
   filelist   : pointer to table of files
*/
void print_table(hash_table * htable_ptr, listfile_entry * filelist)
{

   // TO BE COMPLETED

}


/**
   free hash table

   parameters :
   htable_ptr : pointer to hash table
*/
void free_table(hash_table * htable_ptr)
{

  // TO BE COMPLETED

}

// ------------------------------------------------------------------------
// inner functions definitions
// ------------------------------------------------------------------------

// TO BE COMPLETED
