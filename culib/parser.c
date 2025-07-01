#include "parser.h"

void removeChar(char* str, char ch) {
    char* read = str;
    char* write = str;

    while (*read) {
        if (*read != ch) {
            *write = *read;
            write++;
        }
        read++;
    }
    *write = '\0';
}

int charisdigit(char c) {
    return (c >= '0' && c <= '9');
}

void char_strcat(char* string, char character) {
    char end[] = {character, '\0'};
    strcat(string, end);
}

result* evaluate(const char* expression) {
    static result return_val = {.value = 0.0f, .exit_code = 0};
    if (expression == NULL || strlen(expression) == 0) return NULL;

    // Removing White spaces
    char* dummy = strdup(expression);
    removeChar(dummy, ' ');
    expression = (const char*) dummy;

    // Allocating memory for numbers and operators
    float* numbers = (float*) calloc(1, sizeof(float));
    unsigned int nof = 0;
    char* operators = (char*) calloc(1, sizeof(char));
    unsigned int noo = 0;

    if (numbers == NULL || operators == NULL) {
        free(dummy);
        free(operators);
        free(numbers);
        return_val.exit_code = 1; // Memory allocation error
        return &return_val;
    }

    // We have to now parse the expression and get all the numbers and operators
    char* catcher = (char*) calloc(MAXIMUM_NUMBER_SIZE, sizeof(char));
    if (catcher == NULL) {
        free(catcher);
        free(operators);
        free(dummy);
        free(numbers);
        return_val.exit_code = 1; // Memory allocation error
        return &return_val;
    }

    for (size_t i = 0; i < strlen(expression); i++) {
        char c = expression[i];
        if (charisdigit(c) || c == '.') {
            char_strcat(catcher, expression[i]);
        } else {
            // Copy the catcher to numbers array
            float num = atof(catcher);
            numbers[nof++] = num;
            numbers = (float*) realloc(numbers, (nof + 1) * sizeof(float));

            // empty the catcher string.
            memset(catcher, '\0', MAXIMUM_NUMBER_SIZE);

            // Copy the operator.
            operators[noo++] = expression[i];
            operators = (char*) realloc(operators, (noo + 1) * sizeof(char));
        }
    }
    // Copy the last number if any
    float num = atof(catcher);
    numbers[nof++] = num;
    numbers = (float*) realloc(numbers, (nof + 1) * sizeof(float));
    memset(catcher, '\0', MAXIMUM_NUMBER_SIZE);

    numbers[nof] = 0.0f;
    operators[noo] = '\0';

    // Do something with the information obtained.
    float result_val = 0.0f;
    for (size_t i = 0; i < noo; i++) {
        float a = numbers[i];
        float b = numbers[i + 1];
        char op = operators[i];

        if (result_val == 0.0f) result_val = a;

        switch (op) {
            case '+': {
                result_val += b;
                break;
            }

            case '-': {
                result_val -= b;
                break;
            }

            case '*': {
                result_val *= b;
                break;
            }

            case '/': {
                result_val /= b;
                break;
            }

            default: {
                fprintf(stderr, "Unknown operator: %c\n", op);
                free(catcher);
                free(operators);
                free(dummy);
                free(numbers);
                break;
            }
        }
    }

    return_val.value = result_val;
    return_val.exit_code = 0; // Success

    // Free every allocated memory
    free(catcher);
    free(operators);
    free(dummy);
    free(numbers);
    
    return &return_val;
}
