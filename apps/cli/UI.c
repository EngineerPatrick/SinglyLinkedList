/**
*   
*   @file UI.c
*
*   @brief Application to create and manage a singly linked list with a UI
*   and an iterator struct implementation.
*
*   @details Featuring: architectural modularity, encapsulation and opaque structs,
*   defensive checks and centralized error codes, robust input handling
*   and cleanup paths to avoid memory leaks.
*   
*   Author: Patrick Ferretti
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "singly_linked_list.h"
#include "UI_input.h"
#include "UI_output_error.h"

/**
*   
*   @brief  Calls both list_delete and iterator_delete.
*
*   @param  **list_ptr          Address of the pointer to the list container
*   @param  **it_ptr            Address of the pointer to the iterator
*
*   @pre    **list_ptr != NULL, *list_ptr != NULL, **it_ptr != NULL, *it_ptr != NULL
*   @pre    list_create and iterator_create must have been called
*   @post   If passed parameters are invalid calls exit(EXIT_FAILURE)
*   
*   @note   If an internal error occurs all dynamic memory is freed by this function before closing the application to prevent memory leaks.
*
*/
void memory_freeall(List** list_ptr, It** it_ptr);

int main(void) {
    
    It* it_ptr = NULL;
    List* list_ptr = NULL;

    size_t list_size = 0;
    size_t position = 0;
    int node_data = 0;
    int search_data = 0;
    int option = 0;
    int error_code = 0;
    int found = 0;

    printf("With this program it is possible to create and manage a singly linked list of maximum 100 nodes where every node \n");
    printf("can hold only 1 signed integer, therefore every integer must be within positive or negative 2,147,483,647.\n");
    
    while (option != 7) {
        printf("\n1) Create the list\n2) Print the list\n3) Search data in the list\n4) Insert a new node in the list\n");
        printf("5) Remove a node from the list\n6) Delete the list \n7) Quit the application\n\nEnter the option: ");
        error_code = error_check_data(1, 7, &option);

        if (error_code == INERR_PARAM) {
            printf("Internal error: invalid parameters passed to error_check_data (lower_bound > higher_bound)");
            exit(EXIT_FAILURE);
        }

        while (error_code != INERR_VALID) {
        
            switch (error_code) {
            
                case INERR_FGETS:
                    printf("\nInternal error: fgets() returned NULL in error_check_size, returning size of 0\n");
                    memory_freeall(&list_ptr, &it_ptr);
                    exit(EXIT_FAILURE);
            
                case INERR_RANGE:
                    printf("\nError: the entered input is a number outside of range, the data must be a number between 1 and 7\n");
                    break;

                case INERR_INVALID:
                    printf("\nError: the entered input has a character that is not a number, the data must be a number between 1 and 7\n");
                    break;

                case INERR_OVERFLOW:
                    printf("\nError: the entered input is too long and caused buffer overflow, the option must be a number between 1 and 7\n");
                    break;
            }

            printf("\n1) Create the list\n2) Print the list\n3) Search data in the list\n4) Insert a new node in the list\n");
            printf("5) Remove a node from the list\n6) Delete the list \n7) Quit the application\n\nEnter again the option: ");
            error_code = error_check_data(1, 7, &option);
        }

        error_code = 0;

        switch (option) {
            
            case 1:
                
                if (list_ptr != NULL) {
                    printf("\nError: the list has already been created\n");
                    printf("\nTo create a new one first delete the existing one by entering option 6\n");
                    break;
                }

                /** @note 100 is an arbitrary number and can be changed here */
                if(input_size(100, &list_size) != INERR_VALID) {
                    exit(EXIT_FAILURE);
                }

                error_code = list_create(list_size, &list_ptr);

                if (error_check_list_create(error_code) != ERR_OK) {
                    exit(EXIT_FAILURE);
                }

                error_code = iterator_create(&it_ptr);

                if (error_check_iterator_create(error_code) != ERR_OK) {
                    error_code = list_delete(&list_ptr);

                    if (error_check_list_delete(error_code) != ERR_OK) {
                        exit(EXIT_FAILURE);
                    }

                    exit(EXIT_FAILURE);
                }

                error_code = iterator_tohead(list_ptr, it_ptr);

                if (error_check_iterator_tohead(error_code) != ERR_OK) {
                    memory_freeall(&list_ptr, &it_ptr);
                    exit(EXIT_FAILURE);
                }

                position = 1;

                while (1) {
                    
                    if (input_data(position, -2147483647, 2147483647, 1, &node_data) != INERR_VALID) {
                        memory_freeall(&list_ptr, &it_ptr);
                        exit(EXIT_FAILURE);
                    }

                    error_code = iterator_setdata(it_ptr, node_data);

                    if (error_check_iterator_setdata(error_code, position) != ERR_OK) {
                        memory_freeall(&list_ptr, &it_ptr);
                        exit(EXIT_FAILURE);
                    }

                    error_code = iterator_tonext(it_ptr);

                    if (error_check_iterator_tonext(error_code, position) != ERR_OK) {
                        memory_freeall(&list_ptr, &it_ptr);
                        exit(EXIT_FAILURE);
                    }

                    error_code = iterator_isnull(it_ptr);

                    if (error_code == ERR_NODE_NULL) {
                        break;
                    }

                    else if (error_check_iterator_isnull(error_code) != ERR_OK) {
                        memory_freeall(&list_ptr, &it_ptr);
                        exit(EXIT_FAILURE);
                    }

                    position++;
                }

                list_size = 0;
                position = 0;
                node_data = 0;               
                break;
            
            case 2:
                
                if (list_ptr == NULL) {
                    printf("\nError: the list has not been created yet\n");
                    printf("\nTo create one enter option 1\n");
                    break;
                }

                error_code = iterator_tohead(list_ptr, it_ptr);

                if (error_check_iterator_tohead(error_code) != ERR_OK) {
                    memory_freeall(&list_ptr, &it_ptr);
                    exit(EXIT_FAILURE);
                }

                position = 1;

                while (1) {
                    error_code = iterator_getdata(it_ptr, &node_data);

                    if (error_check_iterator_getdata(error_code, position) != ERR_OK) {
                        memory_freeall(&list_ptr, &it_ptr);
                        exit(EXIT_FAILURE);
                    }

                    printf("\nData of the node %zu: %d\n", position, node_data);

                    error_code = iterator_tonext(it_ptr);

                    if (error_check_iterator_tonext(error_code, position) != ERR_OK) {
                        memory_freeall(&list_ptr, &it_ptr);
                        exit(EXIT_FAILURE);
                    }

                    error_code = iterator_isnull(it_ptr);

                    if (error_code == ERR_NODE_NULL) {
                        break;
                    }

                    else if (error_check_iterator_isnull(error_code) != ERR_OK) {
                        memory_freeall(&list_ptr, &it_ptr);
                        exit(EXIT_FAILURE);
                    }

                    position++;
                }

                position = 0;
                break;
            
            case 3:

                if (list_ptr == NULL) {
                    printf("\nError: the list has not been created yet\n");
                    printf("\nTo create one enter option 1\n");
                    break;
                }

                error_code = iterator_tohead(list_ptr, it_ptr);

                if (error_check_iterator_tohead(error_code) != ERR_OK) {
                    memory_freeall(&list_ptr, &it_ptr);
                    exit(EXIT_FAILURE);
                }

                position = 1;

                if (input_data(position, -2147483647, 2147483647, 3, &search_data) != INERR_VALID) {
                    memory_freeall(&list_ptr, &it_ptr);
                    exit(EXIT_FAILURE);
                }

                while (1) {
                    error_code = iterator_getdata(it_ptr, &node_data);

                    if (error_check_iterator_getdata(error_code, position) != ERR_OK) {
                        memory_freeall(&list_ptr, &it_ptr);
                        exit(EXIT_FAILURE);
                    }

                    if (node_data == search_data) {
                        printf("\nThe data was found in node %zu\n", position);
                        found = 1;
                    }

                    error_code = iterator_tonext(it_ptr);

                    if (error_check_iterator_tonext(error_code, position) != ERR_OK) {
                        memory_freeall(&list_ptr, &it_ptr);
                        exit(EXIT_FAILURE);
                    }

                    error_code = iterator_isnull(it_ptr);

                    if (error_code == ERR_NODE_NULL) {
                        break;
                    }

                    else if (error_check_iterator_isnull(error_code) != ERR_OK) {
                        memory_freeall(&list_ptr, &it_ptr);
                        exit(EXIT_FAILURE);
                    }

                    position++;
                }
                
                if (found == 0) {
                    printf("\nThe data was not found in the list\n");
                }

                position = 0;
                search_data = 0;
                found = 0;
                break;

            case 4:

                if (list_ptr == NULL) {
                    printf("\nError: the list has not been created yet\n");
                    printf("\nTo create one enter option 1\n");
                    break;
                }

                error_code = list_getsize(list_ptr, &list_size);

                if (error_check_list_getsize(error_code) != ERR_OK) {
                    memory_freeall(&list_ptr, &it_ptr);
                    exit(EXIT_FAILURE);
                }

                if (input_position(list_size, 1, &position) != INERR_VALID) {
                    memory_freeall(&list_ptr, &it_ptr);
                    exit(EXIT_FAILURE);
                }
                
                if (input_data(position, -2147483647, 2147483647, 2, &node_data) != INERR_VALID) {
                    memory_freeall(&list_ptr, &it_ptr);
                    exit(EXIT_FAILURE);
                }

                error_code = list_insert(list_ptr, node_data, position);

                if (error_check_list_insert(error_code, position) != ERR_OK) {
                    memory_freeall(&list_ptr, &it_ptr);
                    exit(EXIT_FAILURE);
                }

                list_size = 0;
                position = 0;
                node_data = 0;
                break;

            case 5:

                if (list_ptr == NULL) {
                    printf("\nError: the list has not been created yet\n");
                    printf("\nTo create one enter option 1\n");
                    break;
                }

                error_code = list_getsize(list_ptr, &list_size);

                if (error_check_list_getsize(error_code) != ERR_OK) {
                    memory_freeall(&list_ptr, &it_ptr);
                    exit(EXIT_FAILURE);
                }

                if (list_size == 1) {
                    error_code = list_delete(&list_ptr);

                    if (error_check_list_delete(error_code) != ERR_OK) {
                        memory_freeall(&list_ptr, &it_ptr);
                        exit(EXIT_FAILURE);
                    }

                    error_code = iterator_delete(&it_ptr);

                    if (error_check_iterator_delete(error_code) != ERR_OK) {
                        memory_freeall(&list_ptr, &it_ptr);
                        exit(EXIT_FAILURE);
                    }
                    break;
                }

                if (input_position(list_size, 2, &position) != INERR_VALID) {
                    memory_freeall(&list_ptr, &it_ptr);
                    exit(EXIT_FAILURE);
                }
                
                error_code = list_remove(list_ptr, position);
                
                if (error_check_list_remove(error_code, position) != ERR_OK) {
                    memory_freeall(&list_ptr, &it_ptr);
                    exit(EXIT_FAILURE);
                }

                list_size = 0;
                position = 0;
                break;
                
            case 6:

                if (list_ptr == NULL) {
                    printf("\nError: the list has not been created yet\n");
                    printf("\nTo create one enter option 1\n");
                    break;
                }

                memory_freeall(&list_ptr, &it_ptr);

                break;

            case 7:

                printf("\nQuitting the application...\n\n");

                if (list_ptr == NULL) {
                    break;
                }

                memory_freeall(&list_ptr, &it_ptr);

                break;
        }
    }

    exit(EXIT_SUCCESS);
}

void memory_freeall(List** list_ptr, It** it_ptr) {
    int error_code = 0;
    
    error_code = list_delete(list_ptr);

    if (error_check_list_delete(error_code) != ERR_OK) {
        exit(EXIT_FAILURE);
    }

    error_code = iterator_delete(it_ptr);

    if (error_check_iterator_delete(error_code) != ERR_OK) {
        exit(EXIT_FAILURE);
    }
}