#define _GNU_SOURCE

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define Buffer_SIZE =6969

int isDir(char* path) {
   struct stat st;

   if (stat(path, &st) == -1) {
       printf("Error: could not get information about %s\n", path);
       return -1;
   }

   return S_ISDIR(st.st_mode);
}


int main(int argc, char *argv[]) {
    int DestinDir = isDir(argv[argc-1]);

    if(argc <3){
        printf("Not Enough Arguements");
        return;
    }

    if((argc ==3)&& (!DestinDir)){
        copyFile(argv[1],argv[2]);

    }

    else if((argc==3)&& (DestinDir)){
       copyFile(argv[1],argv[2]);
    }
    
    else if((argc >3)&& (DestinDir)){
        copyFilesToDir(argv,argc-2,argv[argc-1]);
    }
    
    else{
        printf("invalid arguemnts");
        exit(-1);
    }
   
    return 0;
}
