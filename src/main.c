#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "functions.h"

//------------------------------------------------------------------------

int
main()
{
  // create hash table
 hash_table * hashtableptr = create_table();

  // create filelist array
 listfile_entry * filelistptr = create_filelist(MAX_FILES);

  // display menu
  while (1) {
    int nbchoices = 0;
    fprintf(stderr, "\nChoisir une action\n");
    fprintf(stderr, "%d. Load a file in dictionary\n", ++nbchoices);
    fprintf(stderr, "%d. Search a word in dictionary\n", ++nbchoices);
    fprintf(stderr, "%d. Remove file from dictionary\n", ++nbchoices);
    fprintf(stderr, "\n");
    fprintf(stderr, "%d. Print dictionary\n", ++nbchoices);
    fprintf(stderr, "%d. Print file list\n", ++nbchoices);
    fprintf(stderr, "\n0. Quit\n");
    int choice;
    while (1) {
      fprintf(stderr, "Your choice ? ");
      scanf("%d", & choice);
      if (choice >= 0 && choice <= nbchoices) { break; }
      fprintf(stderr, "\nError %d is an incorrect choice\n", choice);
    }
    if (choice == 0) { break; }

    fprintf(stderr, "-------------------------------------------------\n");

    switch (choice) {

      // Load a file in dictionary
    case 1:
      fprintf(stderr, "Filename to Load ? \n");
      char * filetoload; //a corriger plus tard, path dossier
      filetoload = (char *)malloc(sizeof(char) * MAX_LENGTH);
      scanf("%s", filetoload);
      add_file(filetoload, filelistptr, hashtableptr);
      free(filetoload);
      break;

      // Search a word in dictionary
    case 2:
      	printf("Entrez un mot a rechercher :\n");
      	char wordSearched[MAX_LENGTH]; //a corriger plus tard, path dossier
        scanf("%s", wordSearched);
	      search_word(wordSearched , filelistptr ,hashtableptr);
      break;

      // Remove file from dictionary
    case 3:

      // TO BE COMPLETED

      break;

      // Print dictionary
    case 4:
      print_table(hashtableptr,filelistptr);
      break;

      // Print file list
    case 5:
      print_list(filelistptr);
      break;
    }
    fprintf(stderr, "-------------------------------------------------\n");

  }

  // the end : free allocated memory

  // TO BE COMPLETED

  return 0;
}


