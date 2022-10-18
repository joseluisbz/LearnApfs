#include <stdio.h>
#include <string.h>
#include <getopt.h>


/*

% pwd
/Users/joseluisbz/Documents/C_Ejemplo
%

% ls -al
total 8
drwxr-xr-x   3 joseluisbz  staff   96 Aug 17 16:04 .
drwx------+ 15 joseluisbz  staff  480 Aug 17 16:02 ..
-rw-r--r--@  1 joseluisbz  staff  282 Aug 17 16:04 ExamplePutsGets.c
%

% gcc ExamplePutsGets.c -o ExamplePutsGets   
%

% ls -al                                  
total 80
drwxr-xr-x   4 joseluisbz  staff    128 Aug 17 16:07 .
drwx------+ 15 joseluisbz  staff    480 Aug 17 16:02 ..
-rwxr-xr-x   1 joseluisbz  staff  33612 Aug 17 16:05 ExamplePutsGets
-rw-r--r--@  1 joseluisbz  staff    314 Aug 17 16:05 ExamplePutsGets.c
%

% ExamplePutsGets
zsh: command not found: ExamplePutsGets

On macOS
% ./ExamplePutsGets
%

On Windows!!!
λ .\ExamplePutsGets

% ls -al
total 88
drwxr-xr-x   5 joseluisbz  staff    160 Aug 17 16:09 .
drwx------+ 15 joseluisbz  staff    480 Aug 17 16:02 ..
-rwxr-xr-x   1 joseluisbz  staff  33612 Aug 17 16:05 ExamplePutsGets
-rw-r--r--@  1 joseluisbz  staff    840 Aug 17 16:09 ExamplePutsGets.c
-rw-r--r--   1 joseluisbz  staff     42 Aug 17 16:09 file.txt
%

% cat file.txt 
This is going to override previous content%
%


https://www.geeksforgeeks.org/difference-strlen-sizeof-string-c-reviewed/
*/

/*
   Reading command line parameters
   https://stackoverflow.com/a/5157549
   https://stackoverflow.com/questions/189972/argument-parsing-helpers-for-c-unix
*/

/*
https://pablohaya.com/2013/10/12/diferencia-entre-scanf-gets-y-fgets/
*/

/*

https://www.tutorialspoint.com/c_standard_library/c_function_scanf.htm

https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
https://stackoverflow.com/a/2751636

https://stackoverflow.com/questions/7414983/how-to-use-the-ansi-escape-code-for-outputting-colored-text-on-console
https://en.wikipedia.org/wiki/ANSI_escape_code
*/

int main (int num_arg, char **arg_array) {

   printf( "número de argumentos: %d\n", num_arg);
   for (int i = 0; i < num_arg; ++i) {
      printf("arg_array[%d]: %s\n", i, arg_array[i]);
   }
   printf("\n");

   char init_string[] = "Jose";
   char second_string[] = "This is going to override 'Jose' previous content";
   char read_string[strlen(init_string)];
   printf("The String Length is %lu\n", strlen(init_string));
   printf("Size is %lu for: \n%s\n\n", strlen(second_string), second_string);


   char filename[10]="file.txt";
   remove(filename);

   FILE *fp;
   fpos_t init_position, curr_position;

   fp = fopen(filename,"w+");
   fgetpos(fp, &init_position);
   printf("Initial Posicion:");
   /*
   https://stackoverflow.com/a/39587990
   */
   for (size_t i = 0; i < sizeof(init_position); i++) {
      printf("%02X", ((unsigned char *)&init_position)[i]);
   }
   printf("\n");


   /*Se escribe init_string*/
   fputs(init_string, fp);
   printf("Was written the Initial String:%s\n\n", init_string);
   fgetpos(fp, &curr_position);
   printf("Current Posicion: %lu:", curr_position);
   for (size_t i = 0; i < sizeof(curr_position); i++) {
      printf("%02X", ((unsigned char *)&curr_position)[i]);
   }
   printf("\n\n");


/*
   https://www.tutorialspoint.com/c_standard_library/c_function_fseek.htm
   https://stackoverflow.com/a/55289535
*/

   /*Se leen 2 caracteres desde la posición 2*/
   fseek(fp, 2, SEEK_SET);
   printf( "%s\n", fgets(read_string, 3, fp));
   printf("Was read 2 characters from position 2\n\n");


   /*Se leen 4 caracteres desde la posición 0*/
   fsetpos(fp, &init_position);
   fgets(read_string, sizeof(init_string), fp);
   printf( "\"%s\"\n", read_string);
   printf("Was read Initial String characters from position 0\n\n");


   /*Se escribe second_string*/
   fsetpos(fp, &init_position);
   fputs(second_string, fp);
   printf("Was written the Second String:\n%s\n", second_string);
   fgetpos(fp, &curr_position);
   printf("Current Posicion (After Write): %lu:", curr_position);
   for (size_t i = 0; i < sizeof(curr_position); i++) {
      printf("%lu", ((unsigned char *)&curr_position)[i]);
   }
   printf("\n");


   /*Obtener el tamaño del archivo*/
   /*
   https://www.tutorialspoint.com/c_standard_library/c_function_ftell.htm
   */
   long sizeFile = ftell(fp);
   printf("Size of file: %lu\n\n", sizeFile);


   /*Se mueve el cursor 30 posiciones hacia atras desde el final del archivo*/
   fseek(fp, -30, SEEK_CUR);
   fgetpos(fp, &curr_position);
   printf("Current Posicion: %lu:", curr_position);
   for (size_t i = 0; i < sizeof(curr_position); i++) {
      printf("%lu", ((unsigned char *)&curr_position)[i]);
   }
   printf("\n\n");


   /*Get String*/
   long size_chunk = sizeFile - curr_position;
   char extracted_string[size_chunk];
   fgets(extracted_string, size_chunk + 1, fp);
   printf("\"%s\"\n", extracted_string);


   /*Buscar cadena dentro de otra*/
   long position_string = strstr(extracted_string, init_string) - extracted_string;
   printf("Position inside of string: %lu, Position in file: %lu", position_string, position_string + curr_position);


   fclose(fp);
   printf("\n");

   int i, j, n;

    for (i = 0; i < 11; i++) {
        for (j = 0; j < 10; j++) {
            n = 10 * i + j;
            if (n > 108) break;
            printf("\033[%dm %3d\033[m", n, n);
        }
        printf("\n");
    }
   
   return(0);
}