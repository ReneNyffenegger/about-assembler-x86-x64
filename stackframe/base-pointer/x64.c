#include <stdio.h>
#include <stdint.h>

#ifdef _MSC_VER

   #todo ...

   #define MOVE_REGISTER_VALUE_TO_VARIABLE(reg, var) \
                                                     \
          __asm mov var, reg;

#elif defined __GNUC__

   #define MOVE_REGISTER_VALUE_TO_VARIABLE(reg, var) \
                                                     \
          asm("movq %%" #reg ", %0\n" :              \
              "=r"( var ));


#else
   #error "Neither Microsoft nor GNU compiler"
#endif


uint64_t  retVal;
uint64_t* basePointer;
uint64_t  RDI, RSI, RDX;

int func(int param_1, char* param_2, int param_3) {

    uint64_t local_1;
    uint64_t local_2;

    MOVE_REGISTER_VALUE_TO_VARIABLE(rbp, basePointer)
    MOVE_REGISTER_VALUE_TO_VARIABLE(rdi, RDI        )
    MOVE_REGISTER_VALUE_TO_VARIABLE(rsi, RSI        )
    MOVE_REGISTER_VALUE_TO_VARIABLE(rdx, RDX        )

    local_1 = 101;
    local_2 = 102;

#ifdef __GNUC__
    printf("RBP -2: Local 2 (gcc)   = %d\n",   basePointer[- 2]);
    printf("RBP -1: Local 1 (gcc)   = %d\n",   basePointer[- 1]);
#elif defined _MSC_VER

# todo
    printf("RBP -2: Local 2 (cl )   = %d\n",   basePointer[- 2]);
    printf("RBP -1: Local 1 (cl )   = %d\n",   basePointer[- 1]);
#else
    #error "Use Microsoft cl or gcc"
#endif

    printf("RBP  0: ?               = %d\n",   basePointer[  0]);

    printf("RBP  1: Return address  = %ld\n",  basePointer[  1]);
    printf("RDI   : Parameter 1     = %d\n",   RDI             );
    printf("RSI   : Parameter 2     = %s\n",   RSI             );
    printf("RDX   : Parameter 3     = %d\n",   RDX             );

    return 42;
}


int main() {

    printf("Address of func         = %ld\n", &func);

 // printf("ESP before call: %d\n", basePointer[0]);
 // MOVE_REGISTER_VALUE_TO_VARIABLE(esp, basePointer)

    func(1, "hello world", 3);

    MOVE_REGISTER_VALUE_TO_VARIABLE(rax, retVal)

    printf("RAX   : Return value    = %ld\n", retVal);

    return 0;
}
