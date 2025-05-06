#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to perform addition
double add(double a, double b) {
    return a + b;
}

// Function to perform subtraction
double subtract(double a, double b) {
    return a - b;
}

// Function to perform multiplication
double multiply(double a, double b) {
    return a * b;
}

// Function to perform division
double divide(double a, double b) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        exit(1);
    }
    return a / b;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <operand1> <operator> <operand2>\n", argv[0]);
        return 1;
    }

    // Parse operands
    double operand1 = atof(argv[1]);
    double operand2 = atof(argv[3]);

    // Get the operator
    char operator = argv[2][0];

    double result;

    // Perform calculation based on the operator
    switch (operator) {
        case '+':
            result = add(operand1, operand2);
            break;
        case '-':
            result = subtract(operand1, operand2);
            break;
        case '*':
            result = multiply(operand1, operand2);
            break;
        case '/':
            result = divide(operand1, operand2);
            break;
        default:
            printf("Error: Invalid operator. Use +, -, *, or /\n");
            return 1;
    }

    // Output the result
    printf("Result: %.2f\n", result);

    return 0;
}
