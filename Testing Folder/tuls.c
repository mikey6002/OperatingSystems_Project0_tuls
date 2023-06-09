/*I use opendir() to oppen current directory and readdir() to entries in directory
then strcat() to concatenate the path for each entry 
if the entry is a directory it will call function allFiles()recursively to read the subfolders until it reaches the end 
*/
#define _GNU_SOURCE

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void allFiles(const char *dirname, int indent){
    //constructing a path
    char path[6969];
    int i;
    DIR *dir;
    dir = opendir(dirname); // want to see directories and files in current directory
    //if state ment if there is an error getting into a directory
  if (!dir){
    return;
  }    
    struct dirent *entry;

    entry = readdir(dir); // This will give some entries or null 

    // while loop to keep reading (iterate) through everything
    while(entry != NULL){
        // if the entry is a directory it will open the read the subfolder
        // "borrowed" and inpired by https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-opendir-open-directory"
          if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) { // compares entry name with "." and comapres with ".." will ignore current and parent folder
            for (i=0; i<indent; i++) 
            {
                if (i%2 == 0 || i == 0)
                    printf("%s", " ");
                else
                    printf(" ");
            }
            printf("%s%s\n", "  ", entry->d_name);
            strcpy(path, dirname);
            strcat(path, "/");
            strcat(path, entry->d_name);
            allFiles(path, indent+4);
        
         }
         // shows next directory 
         entry = readdir(dir);
    }

closedir(dir);
}


void allFiles(const char *dirname, int indent);

int main(int argc, const char *argv[]){
   if( argc == 2 ) {
       DIR *directory = opendir(argv[1]);
       if (directory){
         allFiles(argv[1], 0);
       }
       else{
         printf("cannot open directory");
         return 1;
       }
     }
     else {
        
        allFiles(".", 0);
     }
    return 0;
}

