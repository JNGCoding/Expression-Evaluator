#ifndef EXPRESSION_PARSER_H_
#define EXPRESSION_PARSER_H_

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define MAXIMUM_NUMBER_SIZE 20

typedef struct expr_result {
    float value;
    unsigned int exit_code;
} result;


result* evaluate(const char* expression);

#endif