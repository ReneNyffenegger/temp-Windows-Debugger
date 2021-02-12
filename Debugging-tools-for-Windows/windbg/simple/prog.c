#include "func.h"

int main(int argc, char* argv[]) {

   if (argc < 3) {
     exit(-1);
   }
   
   int number = atoi(argv[2]);
   int charactersWritten = func(argv[1], number);
   printf("characters written: %d\n",charactersWritten);
   
   return 42;
}
