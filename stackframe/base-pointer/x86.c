#include <stdio.h>
#include <stdint.h>

#ifdef _MSC_VER

   #define MOVE_REGISTER_VALUE_TO_VARIABLE(reg, var) \
                                                     \
          __asm mov var, reg;

#elif defined __GNUC__

   #define MOVE_REGISTER_VALUE_TO_VARIABLE(reg, var) \
                                                     \
          asm("movl %%" #reg ", %0\n" :              \
              "=r"( var ));


#else
   #error "Neither Microsoft nor GNU compiler"
#endif


uint32_t  retVal;
uint32_t* basePointer;

int __cdecl func(int param_1, char* param_2, int param_3) {

      int local_1;
      int local_2;

      MOVE_REGISTER_VALUE_TO_VARIABLE(ebp, basePointer)

      local_1 = 101;
      local_2 = 102;

#ifdef __GNUC__
      printf("EBP -4: Local 2 (gcc)   = %d\n",   basePointer[- 4]);
      printf("EBP -3: Local 1 (gcc)   = %d\n",   basePointer[- 3]);
#elif defined _MSC_VER
      printf("EBP -2: Local 2 (cl )   = %d\n",   basePointer[- 2]);
      printf("EBP -1: Local 1 (cl )   = %d\n",   basePointer[- 1]);
#else
      #error "Use Microsoft cl or gcc"
#endif

      printf("EBP  0: ?               = %d\n",   basePointer[  0]);

      printf("EBP  1: Return address  = %d\n",   basePointer[  1]);
      printf("EBP  2: Parameter 1     = %d\n",   basePointer[  2]);
      printf("EBP  3: Parameter 2     = %s\n",   basePointer[  3]);
      printf("EBP  4: Parameter 3     = %d\n",   basePointer[  4]);

      return 42;
}


int main() {

    printf("Address of func         = %d\n", &func);

 // printf("ESP before call: %d\n", basePointer[0]);
 // MOVE_REGISTER_VALUE_TO_VARIABLE(esp, basePointer)

    func(1, "hello world", 3);

    MOVE_REGISTER_VALUE_TO_VARIABLE(eax, retVal)

    printf("EAX   : Return value    = %d\n", retVal);

    return 0;
}
