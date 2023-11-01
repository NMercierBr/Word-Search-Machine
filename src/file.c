#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "functions.h" // extern functions declarations

// ------------------------------------------------------------------------
// inner functions declarations
// ------------------------------------------------------------------------

// TO BE COMPLETED

//------------------------------------------------------------------------
// global functions definitions
//------------------------------------------------------------------------

/**
   Create and initialize file table of capacity maxfiles

   parameters :
   maxfiles : capacity of file table

   returns : pointer to table or NULL in case of error
 */
listfile_entry * create_filelist(int maxfiles) {

  listfile_entry * entry_ptr = (listfile_entry*) malloc(maxfiles * sizeof(listfile_entry));
   for(int i = 0; i < maxfiles ; i++ ){
	 entry_ptr[i].filename[0] = '\0';
	 entry_ptr[i].loaded = 0;
}
  return entry_ptr; 
}

/**
   parameters :
   filename   : name of file :)
   filelist   : pointer to table of files

   returns :
    1 if file already present in table
    0 else
*/
int is_Present(char filename[],listfile_entry * filelist)
{
	for(int i = 0 ; i < MAX_FILES ; i++ ){
		if(strcmp(filelist[i].filename ,filename) == 0) {
			printf("file already present in table");
			return 1;
		}
	}
  return 0;
}

/**
   add words from file to table
   - checks if the file has already been loaded
   - updates the file table (if file not already loaded)
   - reads every word in the file (idem)
   - updates the hash table (idem)

   parameters :
   filename   : name of file :)
   filelist   : pointer to table of files
   htable_ptr : pointer to hash table

   returns :
    1 if file already present in table
    2 if no space left in filelist
   -1 if file doesn't exist or can't be read
   -2 if allocation error
    0 if everything ok
*/
int add_file(char filename[],listfile_entry * filelist, hash_table * htable_ptr)
{
  FILE *fp;
  fp = fopen(filename, "r");
   if(fp == NULL) {
      perror("Error opening file, or can't be read\n");
      fclose(fp);
      return(-1);
  }
	if(is_Present(filename,filelist)) { 
    perror("File already present in table\n");
    fclose(fp);
    return 1; }
	else {
	int i =0;
		while(filelist[i].filename[0]!='\0'){
		  i++;
      if (i == MAX_FILES ) {
        perror("No space left in filelist\n");
        fclose(fp);
        return 2;
      }
		}
    strcpy(filelist[i].filename, filename);
    
		filelist[i].loaded=1;
    //load dans la hashtable, -> update table

    char wordactuel[MAX_LENGTH];
    int k, j ;
    wordactuel[0] = '\0';
    
    while(fscanf(fp, " %50s" , wordactuel) == 1) {
       char *token = strtok(wordactuel, "'");
        while (token != NULL) {
        for(k =0, j = 0 ; wordactuel[k] ; k++){
          if (isalpha(wordactuel[k])){
            wordactuel[j++] = tolower(wordactuel[k]);
          }
        } 

      wordactuel[j] = '\0';
     
      if(strlen(wordactuel) > 0){
      update_table(htable_ptr,wordactuel,filelist[i].filename,i); //update table si erreur retourne -2
    }
    token = strtok(NULL, "'");
      }
    }
	}
  fclose(fp);
  return 0; // all fine
} 


/**
   remove file from file table

   parameters :
   filename   : name of file to remove
   filelist   : pointer to table of files
   htable_ptr : pointer to hash table

   returns :
   -1 if file not in table
    0 if file removed
*/

//avant de supprimer le file, on vérif
int remove_file(char filename[],listfile_entry * filelist,hash_table * htable_ptr)
{
  if(htable_ptr == NULL||filelist == NULL){
      perror("htable ou filelist non initialisé.\n");
      return 2;
  }
  int i = 0;
  while(strcmp(filelist[i].filename, filename) != 0){
		  i++;
      if(i== MAX_FILES){
        perror("Fichier non présent dans la table.\n");
        return -1;
      }
  }
  //si fichier chargé, recherche dans tout le dictionnaire pour trouver tous les mots et les supprimer
  //lorsque plus de mots du fichier x, on supprime le fichier x de la filelist ( free_filelist())
  // i = index du fichier

  int j = 0;
  while (j < MAX_ENTRIES)
  {
      word_list * word_ptr = &(htable_ptr->htable[j]);
      word_entry * ptr = word_ptr->first_word;

    while (ptr != NULL);
    {
      if(strcmp(ptr->in_file,i) == 1){
          //ON SUPPRIME : on réarrange la chaine de next et on free
        if(word_ptr->first_word == ptr){  //cas ou le mot est la tête de liste
          word_ptr->first_word = ptr->next;
          free(ptr);
        }
        else if(word_ptr->last_word == ptr) { //cas ou le mot est la queue de liste

        }
        else {

        }

      }
      ptr=ptr->next;
    }
    j++;
  }
  

  return 0;
}


/*
  print file table (only loaded files)

  parameters :
   filelist : pointer to table of files
*/
void print_list(listfile_entry * filelist)
{
  if(filelist!= NULL){
  int i = 0;
  while (filelist[i].loaded == 1)
  {
    printf("Le fichier %s est chargé.\n", filelist[i].filename);
    i++;
    }
  }
}

/**
   free file table

parameters :
   filelist   : pointer to table of files
*/
void
free_filelist(listfile_entry * filelist)
{
  // TO BE COMPLETED
}

// ************************************************************************
// inner functions
// ************************************************************************

// TO BE COMPLETED

