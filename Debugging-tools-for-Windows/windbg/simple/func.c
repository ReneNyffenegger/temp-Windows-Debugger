/*
 

   There are basically two types of functions.
     - A function that requires a stack frame is called a frame function.
     - A function that does not require a stack frame is called a leaf function.

     A frame function is a function that allocates stack space, calls other
     functions, saves nonvolatile registers, or uses exception handling.

     It also requires a function table entry.

     A frame function requires a prolog and an epilog. 

     If a frame function does not call another function then it is not required
     to align the stack

     A leaf function is one that does not require a function table entry. It
     can't make changes to any nonvolatile registers, including RSP, which
     means that it can't call any functions or allocate stack space.


   Prolog
     Every function that
       - allocates stack space,
       - calls other functions,
       - saves nonvolatile registers, or
       - uses exception handling
     must have a prolog whose address limits are described in the unwind data
     associated with the respective function table entry. 

     The prolog
       - saves argument registers in their home addresses if necessary,
       - pushes nonvolatile registers on the stack,
       - allocates the fixed part of the stack for locals and temporaries, and
       - optionally establishes a frame pointer.

             mov    [RSP + 8], RCX               ; store the argument register RCX in its home location,
             push   R15                          ; save nonvolatile registers R13-R15
             push   R14
             push   R13
             sub    RSP, fixed-allocation-size   ; allocate the fixed part of the stack frame,
             lea    R13, 128[RSP]                ;  establishes a frame pointer that points 128 bytes into the fixed allocation area.


     Epilog / https://docs.microsoft.com/en-us/cpp/build/prolog-and-epilog?view=msvc-160
       Epilog code exists at each exit to a function.

       Whereas there is normally only one prolog, there can be many epilogs.

       Epilog code
         - trims the stack to its fixed allocation size (if necessary),
         - deallocates the fixed stack allocation,
         - restores nonvolatile registers by popping their saved values from the stack, and
         - returns.

               add      RSP, fixed-allocation-size
               pop      R13
               pop      R14
               pop      R15
               ret


   Stack allocation ( https://docs.microsoft.com/en-us/cpp/build/stack-usage?view=msvc-160 )

     Function prolog

        A function's prolog is responsible for allocating stack space for local
        variables, saved registers, stack parameters, and register parameters.

     Parameter area

        The parameter area is always at the bottom of the stack (even if alloca
        is used), so that it will always be adjacent to the return address
        during any function call. 

        It contains at least four entries, but always enough space to hold all
        the parameters needed by any function that may be called

     The stack will always be maintained 16-byte aligned


     Frame pointer

        If a frame pointer is used, the option exists to dynamically create the
        parameter stack area. This is not currently done in the x64 compiler.





*/
#include <stdio.h>
#include <windows.h>

#include "func.h"



int func_leave() {
    return 99;
}

int func(
     unsigned long long addr_last_var_caller,
     unsigned long long addr_caller,
     const char* filename,
     int number) {


   unsigned long long addr_last_parameter  = (unsigned long long) &number;
   unsigned long long addr_2nd_last_param  = (unsigned long long) &filename;
   unsigned long long ret_addr             = (unsigned long long) *((unsigned long long*) addr_last_parameter + 8);

   printf("func: addr_last_var_caller - addr_last_parameter: %llu\n", addr_last_var_caller - addr_last_parameter);
   printf("func: addr_last_parameter  - addr_2nd_last_param: %llu\n", addr_last_parameter  - addr_2nd_last_param);
   printf("func: ret_addr             - addr_caller        : %llu\n", ret_addr             - addr_caller        );

   FILE* f = fopen(filename, "w");
   int charactersWritten = fprintf(f, "The number is %d\n", number);
   fclose(f);

   MessageBox(0, "done", "message", 0);

   return charactersWritten * func_leave();

}
