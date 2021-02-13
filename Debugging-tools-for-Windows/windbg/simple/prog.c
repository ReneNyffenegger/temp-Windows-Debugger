#include "func.h"

int main(int argc, char* argv[]) {

   if (argc < 3) {
       exit(-1);
   }

   char*              filename       = argv[1];
   char*              number_as_text = argv[2];

   unsigned long long addr_1st_arg   = (unsigned long long) &argc;
   unsigned long long addr_2nd_arg   = (unsigned long long) &argv;

   unsigned long long addr_1st_var   = (unsigned long long) &filename;
   unsigned long long addr_2nd_var   = (unsigned long long) &number_as_text;
   unsigned long long addr_3rd_var   = (unsigned long long) &addr_1st_arg;

   unsigned long long addr_main      = (unsigned long long) &main;
   unsigned long long addr_func      = (unsigned long long) &func;

// unsigned long long argv_addr_addr = (unsigned long long) &addr_2nd_arg;
// unsigned long long main_addr      = (unsigned long long) &main;


   printf("addr_2nd_arg - addr_1st_arg : %llu\n", addr_2nd_arg - addr_1st_arg);
   printf("addr_1st_var - addr_2nd_arg : %llu\n", addr_1st_var - addr_2nd_var);
   printf("addr_1st_var - addr_2nd_var : %llu\n", addr_1st_var - addr_2nd_var);
   printf("addr_2nd_var - addr_3rd_var : %llu\n", addr_2nd_var - addr_3rd_var);

   printf("addr_main    - addr_func    : %llu\n", addr_main    - addr_func   );
   
   int number = atoi(number_as_text);

   int charactersWritten = 257;

   charactersWritten = func(
      (unsigned long long) &charactersWritten,
                            addr_main,
                            filename,
                            number
      );
   printf("characters written: %d\n",charactersWritten);
   
   return 42;
}
