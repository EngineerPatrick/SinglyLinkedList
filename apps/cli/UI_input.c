/**
*   
*   @file UI_input.c
*
*   @brief Implementation for the UI_inpt module.
*
*   @details Contains the input and the error handling logic.
*   Output strings representing each error case. 
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "UI_input.h"

int input_size(size_t upper_bound, size_t* list_size) {
    size_t input = 0;
    int error_code = 0;

    if (upper_bound == 0) {
        return INERR_PARAM;
    }

    if (list_size == NULL) {
        return INERR_NULL;
    }
    
    printf("\nEnter the size of the list: ");
    error_code = error_check_size(upper_bound, &input);

    while (error_code != INERR_VALID) {
        
        switch (error_code) {
            
            case INERR_FGETS:
                printf("\nInternal error: fgets() returned NULL in error_check_size\n");
                return INERR_FGETS;
            
            case INERR_RANGE:
                printf("\nError: the entered input is a number outside of range, the size must be a number between 1 and %zu\n", upper_bound);
                break;

            case INERR_INVALID:
                printf("\nError: the entered input has a character that is not a number, the size must be a number between 1 and %zu\n", upper_bound);
                break;

            case INERR_OVERFLOW:
                printf("\nError: the entered input is too long and caused buffer overflow, the size must be a number between 1 and %zu\n", upper_bound);
                break;
        }

        printf("\nEnter again the size of the list: ");
        error_code = error_check_size(upper_bound, &input);
    }

    *list_size = input;
    return INERR_VALID;
}

int input_data(size_t position, int lower_bound, int upper_bound, int option, int* node_data) {
    int input = 0;
    int error_code = 0;

    if (position == 0) {
        return INERR_POS;
    }

    if (lower_bound > upper_bound) {
        printf("Internal error: invalid parameters passed to the function error_check_data (lower_bound > upper_bound)");
        return INERR_PARAM;
    }

    if (node_data == NULL) {
        return INERR_NULL;
    }

    if (option == 1) {
        printf("\nEnter the data of node %zu: ", position);
    }

    else if (option == 2) {
        printf("\nEnter the data of the new node %zu: ", position);
    }

    else {
        printf("\nEnter the data to search in the list: ");
    }

    error_code = error_check_data(lower_bound, upper_bound, &input);
    
    while (error_code != INERR_VALID) {

        switch (error_code) {
            
            case INERR_FGETS:
                printf("\nInternal error: fgets() returned NULL in error_check_data\n");
                return INERR_FGETS;
            
            case INERR_RANGE:
                printf("\nError: the entered input is a number outside of range, the data must be a number between %d and %d\n", lower_bound, upper_bound);
                break;

            case INERR_INVALID:
                printf("\nError: the entered input has a character that is not a number, the data must be a number between %d and %d\n", lower_bound, upper_bound);
                break;

            case INERR_OVERFLOW:
                printf("\nError: the entered input is too long and caused buffer overflow, the data must be a number between %d and %d\n", lower_bound, upper_bound);
                break;
        }

        if (option == 1) {
            printf("\nEnter the data of node %zu: ", position);
        }

        else if (option == 2) {
            printf("\nEnter the data of the new node %zu: ", position);
        }

        else {
            printf("\nEnter the data to search in the list: ");
        }

        error_code =  error_check_data(lower_bound, upper_bound, &input);
    }
    
    *node_data = input;
    return INERR_VALID;
}

int input_position(size_t list_size, int option, size_t* position) {
    size_t input = 0;
    int error_code = 0;

    if (list_size == 0) {
        return INERR_NOSIZE;
    }

    if (position == NULL) {
        return INERR_NULL;
    }

    if (option == 1) {
        printf("\nEnter the position where to insert the node: ");
        list_size++;
    } 
    
    else {
        printf("\nEnter the position of the node to delete: ");
    }

    error_code = error_check_size(list_size, &input);

    while (error_code != INERR_VALID) {
        
        switch (error_code) {
            
            case INERR_FGETS:
                printf("\nInternal error: fgets() returned NULL in error_check_size\n");
                return INERR_FGETS;
            
            case INERR_RANGE:
                printf("\nError: the entered input is a number outside of range, the position must be a number between 1 and %zu\n", list_size);
                break;

            case INERR_INVALID:
                printf("\nError: the entered input has a character that is not a number, the position must be a number between 1 and %zu\n", list_size);
                break;

            case INERR_OVERFLOW:
                printf("\nError: the entered input is too long and caused buffer overflow, the position must be a number between 1 and %zu\n", list_size);
                break;
        }

        if (option == 1) {
            printf("\nEnter the position where to insert the node: ");
        } 
        
        else {
            printf("\nEnter the position of the node to delete: ");
        }

        error_code = error_check_size(list_size, &input);
    }
    
    *position = input;
    return INERR_VALID;
}

int error_check_size(size_t upper_bound, size_t* input) {
    char buffer[22];
    char *end = NULL;
    size_t input_check = 0;
    errno = 0;
    int flush = 0;

    if (upper_bound == 0) {
        return INERR_PARAM;
    }

    if (input == NULL) {
        return INERR_NULL;
    }
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return INERR_FGETS;
    }

    if (buffer[0] == '-') {
         return INERR_RANGE;
    }

    if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] != '\n') {
        while((flush = getchar()) != '\n' && flush != EOF);
        return INERR_OVERFLOW;
    }

    input_check = strtoul(buffer, &end, 10);

    if (*end != '\n' || *end == *buffer) {
        return INERR_INVALID;
    }

    else if (input_check > upper_bound || input_check == 0 || errno == ERANGE) {
        errno = 0;
        return INERR_RANGE;
    } 
    
    (*input) = input_check;
    return INERR_VALID;
}

int error_check_data(int lower_bound, int upper_bound, int* input) {
    char buffer[13];
    char *end = NULL;
    long int input_check = 0;
    errno = 0;
    int flush = 0;

    if (lower_bound > upper_bound) {
        return INERR_PARAM;
    }

    if (input == NULL) {
        return INERR_NULL;
    }
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return INERR_FGETS;
    }

    if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] != '\n') {
        while((flush = getchar()) != '\n' && flush != EOF);
        return INERR_OVERFLOW;
    }

    input_check = strtol(buffer, &end, 10);

    if (*end != '\n' || *end == *buffer) {
        return INERR_INVALID;
    }

    else if (input_check < lower_bound || input_check > upper_bound || errno == ERANGE) {
        errno = 0;
        return INERR_RANGE;
    } 
    
    (*input) = (int) input_check;
    return INERR_VALID;
}