#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

int reg_var = 10;      // Regular variable
int reg_reg = 20;      // Regular variable instead of register
volatile int vol_var = 30; // Volatile variable

void second_function() {
    printf("In second_function before longjmp:\n");
    printf("reg_var = %d\n", reg_var);
    printf("reg_reg = %d\n", reg_reg);
    printf("vol_var = %d\n", vol_var);

    // Modify the variables before jumping back
    reg_var = 100;
    reg_reg = 200;
    vol_var = 300;

    // Jump back to the setjmp location
    longjmp(env, 1);
}

int main() {
    int val = setjmp(env);

    if (val == 0) {
        printf("In main, before calling second_function:\n");
        printf("reg_var = %d\n", reg_var);
        printf("reg_reg = %d\n", reg_reg);
        printf("vol_var = %d\n", vol_var);

        // Call the second function
        second_function();

        // This line will be skipped due to longjmp
        printf("This line will be skipped.\n");
    } else {
        // This block is executed after longjmp
        printf("Back in main after longjmp:\n");
        printf("reg_var = %d\n", reg_var);
        printf("reg_reg = %d\n", reg_reg);
        printf("vol_var = %d\n", vol_var);
    }

    return 0;
}
