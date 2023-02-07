#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


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
