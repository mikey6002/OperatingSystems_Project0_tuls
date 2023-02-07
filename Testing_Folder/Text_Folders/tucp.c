#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char** argv) {
   if (argc < 3) {
       printf("Not enough arguments\n");
       exit(-1);
   }

   int isDestinDir = isDir(argv[argc-1]);

   if ((argc == 3) && (!isDestinDir)) {
       copyFile(argv[1], argv[2]);
   }

   else if ((argc == 3) && (isDestinDir)) {
       copyFile(argv[1], argv[2]);
   }

   else if ((argc > 3) && (isDestinDir)) {
       copyFilesToDir(argv, argc-2, argv[argc-1]);
   }

   //Error
   else {
       printf("Invalid arguments\n");
       exit(-1);
   }

   return 0;
}

//https://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c
//Function to copy one file to another
void copyFile(char* sourceFile, char* DestinFile) {
   int srcFd, destFd;
   char buffer[BUFFER_SIZE];
   ssize_t bytes;

   srcFd = open(sourceFile, O_RDONLY);
   destFd = open(DestinFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

   //Error checking
   if (srcFd == -1) {
       printf("Error: could not open source file\n");
       exit(-1);
   }
   if (destFd == -1) {
       printf("Error: could not open destination file\n");
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

//https://stackoverflow.com/questions/7267295/how-can-i-copy-a-file-from-one-directory-to-another-in-c-c
//Function to copy multiple files to a directory
void copyFilesToDir(char** sourceFiles, int numFiles, char* DestinDir) {
   int srcFd, destFd;
   char buffer[BUFFER_SIZE];
   ssize_t bytes;

   //Iterate through the source files
   for (int i=0; i<numFiles; i++) {
       //Create the full path for the destination file
       char DestinFile[strlen(DestinDir) + strlen(sourceFiles[i]) + 1];
       strcpy(DestinFile, DestinDir);
       strcat(DestinFile, "/");
       strcat(DestinFile, sourceFiles[i]);

       //Open the source and destination files
       srcFd = open(sourceFiles[i], O_RDONLY);
       destFd = open(DestinFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

       //Error checking
       if (srcFd == -1) {
           printf("Error: could not open file %s\n", sourceFiles[i]);
           exit(-1);
       }
       if (destFd == -1) {
           printf("Error: could not open destination file %s\n", DestinFile);
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

//https://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file
//Function to check if the given path is a file or a directory
int isDir(char* path) {
   struct stat st;

   //Error checking
   if (stat(path, &st) == -1) {
       printf("Could not get information about %s\n", path);
       exit(-1);
   }

   //Return 1 if the path is a directory, 0 otherwise
   return S_ISDIR(st.st_mode);
}


