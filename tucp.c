#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

// Was in a time crunch studying for midterms  forgive me using a lot of stack overflows ;-;


//https://stackoverflow.com/questions/7267295/how-can-i-copy-a-file-from-one-directory-to-another-in-c-c
//Function to copy one file to another
void copyFile(char* sourceFile, char* destinFile) {
   int sourceFd, destFd;
   char buffer[BUFFER_SIZE];
   ssize_t exp;

   //Open source and destination files
   sourceFd = open(sourceFile, O_RDONLY);
   destFd = open(destinFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

   //Error checking
   if (sourceFd == -1) {
       printf("Could not open source file\n");
        exit(-1);
   }
   if (destFd == -1) {
       printf("Could not open destination file\n");
        exit(-1);
   }

   //Copy the source file to the destination file
   while ((exp = read(sourceFd, buffer, BUFFER_SIZE)) > 0) {
       write(destFd, buffer, exp);
   }

   //Close the files
   close(sourceFd);
   close(destFd);
}

//https://stackoverflow.com/questions/15796503/copying-multiple-files-in-c
//Function to copy multiple files to a directory
void copyFilesToDir(char** sourceFiles, int numFiles, char* destDir) {
   int sourceFd, destFd;
   char buffer[BUFFER_SIZE];
   ssize_t exp;

   //Iterate through the source files
   for (int i=0; i<numFiles; i++) {
       //Create the full path for the destination file
       char destinFile[strlen(destDir) + strlen(sourceFiles[i]) + 1];
       strcpy(destinFile, destDir);
       strcat(destinFile, "/");
       strcat(destinFile, sourceFiles[i]);

       //Open the source and destination files
       sourceFd = open(sourceFiles[i], O_RDONLY);
       destFd = open(destinFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

       //Error checking
       if (sourceFd == -1) {
           printf("Error: could not open file %s\n", sourceFiles[i]);
            exit(-1);
       }
       if (destFd == -1) {
           printf("Error: could not open destination file %s\n", destinFile);
            exit(-1);
       }

       //Copy the source file to the destination file
       while ((exp = read(sourceFd, buffer, BUFFER_SIZE)) > 0) {
           write(destFd, buffer, exp);
       }

       //Close the files
       close(sourceFd);
       close(destFd);
   }
}


//Function to check if the given path is a file or a directory
int isDir(char* path) {
   struct stat st;

    // Checking Error if there is a path
   if (stat(path, &st) == -1) {
       printf("Could not get information about %s\n", path);
       return -1;
   }

   return S_ISDIR(st.st_mode);
}


int main(int argc, char** argv) {
   //Error checking
   if (argc < 3) {
       printf("Error: not enough arguments\n");
       exit(-1);
   }

   //Check if the destination is a directory
   int isDestDir = isDir(argv[argc-1]);

   //Copy one file to another
   if ((argc == 3) && (!isDestDir)) {
       copyFile(argv[1], argv[2]);
   }

   //Copy one file to a directory
   else if ((argc == 3) && (isDestDir)) {
       copyFile(argv[1], argv[2]);
   }

   //Copy multiple files to a directory
   else if ((argc > 3) && (isDestDir)) {
       copyFilesToDir(argv, argc-2, argv[argc-1]);
   }

   //Error
   else {
       printf("Error: invalid arguments\n");
       exit(-1);
   }

   return 0;
}
