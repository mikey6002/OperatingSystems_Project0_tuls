#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define Buffer_SIZE =6969


//https://stackoverflow.com/questions/7267295/how-can-i-copy-a-file-from-one-directory-to-another-in-c-c
void copyFilesToDir(char** sourceFiles, int numFiles, char* destDir) {
   int srcFd, destFd;
   char buffer[BUFFER_SIZE];
   ssize_t bytes;

   //Iterate through the source files
   for (int i=0; i<numFiles; i++) {
       //Create the full path for the destination file
       char destFile[strlen(destDir) + strlen(sourceFiles[i]) + 1];
       strcpy(destFile, destDir);
       strcat(destFile, "/");
       strcat(destFile, sourceFiles[i]);

       //Open the source and destination files
       srcFd = open(sourceFiles[i], O_RDONLY);
       destFd = open(destFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

       //Error checking
       if (srcFd == -1) {
           printf("Error: could not open file %s\n", sourceFiles[i]);
           exit(-1);
       }
       if (destFd == -1) {
           printf("Error: could not open destination file %s\n", destFile);
           exit(-1);
       }

       //Copy the source file to the destination file
       while ((bytes = read(srcFd, buffer, BUFFER_SIZE)) > 0) {
           write(destFd, buffer, bytes);
       }

       //Close the files
       close(srcFd);
       close(destFd);
   }
}







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
