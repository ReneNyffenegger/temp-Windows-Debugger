#include <stdio.h>
#include <windows.h>

#include "func.h"

int func(const char* filename, int number) {

   FILE* f = fopen(filename, "w");
   int charactersWritten = fprintf(f, "The number is %d\n", number);
   fclose(f);

   MessageBox(0, "done", "message", 0);

   return charactersWritten;

}
