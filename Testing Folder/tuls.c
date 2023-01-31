#define _GNU_SOURCE;

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>



void allFiles(const char *dirname){

    DIR *dir;
    dir = opendir(dirname); // want to see directories and files in current directory
    //if state ment if there is an error
    if (dir ==NULL){
        printf("Error");
        return 1;
    }
    printf("Currently Reading files in %s \n", dirname);
    
    struct dirent *entry;
    struct stat file_stat;

    entry = readdir(dir); // This will give some entries or null 

    // while loop to keep reading (iterate) through everything
    while(entry != NULL){
        //constructing a path
        char path[6969];
        //prints file folder name.. etc in the current directory
         printf("%s\n", entry->d_name);
           if ( (entry ->d_type == DT_DIR) && 
               (strcmp(entry ->d_name, ".")  !=0) && 
               (strcmp(entry ->d_name, "..") !=0) ) { // compares entry name with "." and comapres with ".."
            //concat dirname
            strcat(path,dirname);
            strcat(path, "/");
            strcat(path,entry ->d_name);
            allFiles(path);

         }
         entry = readdir(dir);
    }

}


int main(int argc, char const **argv[]){

    allFiles(".");
   return 0;
}

