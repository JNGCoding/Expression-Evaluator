/*
Program Briefing :
This program is a simple C application that evaluates a mathematical expression.

Program Flow :
1) Include the parser.h header file.
2) use the evaluate function to compute the result of a given expression.
3) Printing the result to the stdout.

Program Limitations :
1) Couldn't implement order of operations i.e, PEDMAS or BODMAS.
2) Maximum number size is not dynamic but instead uses a fixed size which can be changed in the header file.
3) Program doesn't understand parenthesis or any-type of grouping. It evaluates the expression from left to right.
4) Error - Checking is not the greatest in the world.
*/

#include <stdio.h>
#include "culib/parser.h"

int main(int argc, char const *argv[]) {
    printf("1.16 + 24.45 + 123 = %f\n", evaluate("1.16 + 24.45 + 123")->value);
    printf("54 * 2 - 103 = %f\n", evaluate("54 * 2 - 103")->value);
    printf("7.2 / 2.0 = %f\n", evaluate("7.2 / 2.0")->value);
    return 0;
}
