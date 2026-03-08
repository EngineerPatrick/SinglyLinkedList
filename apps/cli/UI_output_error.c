/**
*
*   @file UI_output_error.c
*
*   @brief Implementation for the UI_output_error module.
*
*   @details Error output strings adapted for every error case.
*
*/

#include <stdio.h>
#include "UI_output_error.h"
#include "singly_linked_list.h"

int error_check_list_create(int error_code) {

    switch (error_code) {
                             
        case ERR_NOSIZE:
            printf("\nInternal error: invalid parameter passed to list_create (size of the list is 0)\n");
            return ERR_NULL;

        case ERR_NULL:
            printf("\nInternal error: unexpected NULL address of List type pointer in list_create\n");
            return ERR_NULL;
        
        case ERR_NOMEM:
            printf("\nInternal error: memory allocation failed in list_create\n");
            return ERR_NULL;
        
        default:
            break;
    }

    return ERR_OK;
}

int error_check_list_delete(int error_code) {

    switch (error_code) {

        case ERR_NULL:
            printf("\nInternal error: unexpected NULL address of List type pointer in list_delete\n");
            return ERR_NULL;
                             
        case ERR_LIST_NULL:
            printf("\nInternal error: unexpected NULL List type pointer in list_delete\n");
            return ERR_NULL;
        
        default:
            break;
    }

    return ERR_OK;
}

int error_check_list_getsize(int error_code) {

    switch (error_code) {
                             
        case ERR_LIST_NULL:
            printf("\nInternal error: unexpected NULL List type pointer in list_getsize\n");
            return ERR_NULL;
        
        case ERR_NULL:
            printf("\nInternal error: unexpected NULL address of size_t type variable in list_getsize\n");
            return ERR_NULL;
        
        default:
            break;
    }

    return ERR_OK;
}

int error_check_iterator_create(int error_code) {

    switch (error_code) {
                        
        case ERR_NULL:
            printf("\nInternal error: unexpected NULL address of It type pointer in iterator_create\n");
            return ERR_NULL;

        case ERR_NOMEM:
            printf("\nInternal error: memory allocation failed iterator_create\n");
            return ERR_NULL;
        
        default:
            break;
    }

    return ERR_OK;
}

int error_check_iterator_delete(int error_code) {

    switch (error_code) {
                        
        case ERR_NULL:
            printf("\nInternal error: unexpected NULL address of It type pointer in iterator_delete\n");
            return ERR_NULL;
                             
        case ERR_IT_NULL:
            printf("\nInternal error: unexpected NULL It type pointer in iterator_delete\n");
            return ERR_NULL;
        
        default:
            break;
    }

    return ERR_OK;
}

int error_check_iterator_tohead(int error_code) {

    switch (error_code) {

        case ERR_LIST_NULL:
            printf("\nInternal error: unexpected NULL List type pointer in iterator_tohead\n");
            return ERR_NULL;

        case ERR_IT_NULL:
            printf("\nInternal error: unexpected NULL It type pointer in iterator_tohead\n");
            return ERR_NULL;
        
        default:
            break;
    }

    return ERR_OK;
}

int error_check_iterator_tonext(int error_code, size_t position) {
    
    switch (error_code) {
                            
        case ERR_IT_NULL:
            printf("\nInternal error: unexpected NULL It type pointer in iterator_tonext\n");
            return ERR_NULL;

        case ERR_NODE_NULL:
            printf("\nInternal error: unexpected NULL pointer to the node %zu in iterator_tonext\n", position);
            return ERR_NULL;
        
        default:
            break;
    }

    return ERR_OK;
}

int error_check_iterator_getdata(int error_code, size_t position) {
    
    switch (error_code) {
                            
        case ERR_IT_NULL:
            printf("\nInternal error: unexpected NULL It type pointer in iterator_getdata\n");
            return ERR_NULL;

        case ERR_NODE_NULL:
            printf("\nInternal error: unexpected NULL pointer to the node %zu in iterator_getdata\n", position);
            return ERR_NULL;
                            
        case ERR_NULL:
            printf("\nInternal error: unexpected NULL address of int type variable in iterator_getdata\n");
            return ERR_NULL;
        
        default:
            break;
    }

    return ERR_OK;
}

int error_check_iterator_setdata(int error_code, size_t position) {
    
    switch (error_code) {
                            
        case ERR_IT_NULL:
            printf("\nInternal error: unexpected NULL It type pointer in iterator_setdata\n");
            return ERR_NULL;

        case ERR_NODE_NULL:
            printf("\nInternal error: unexpected NULL pointer to the node %zu in iterator_setdata\n", position);
            return ERR_NULL;
        
        default:
            break;
    }

    return ERR_OK;
}

int error_check_iterator_isnull(int error_code) {
    
    switch (error_code) {
                            
        case ERR_IT_NULL:
            printf("\nInternal error: unexpected NULL It type pointer in iterator_isnull\n");
            return ERR_NULL;
        
        default:
            break;
    }

    return ERR_OK;
}

int error_check_list_insert(int error_code, size_t position) {
    
    switch (error_code) {
                            
        case ERR_LIST_NULL:
            printf("\nInternal error: unexpected NULL List type pointer in list_insert\n");
            return ERR_NULL;

        case ERR_POS:
            printf("\nInternal error: invalid parameter passed to list_insert (position > list_size + 1)\n");
            return ERR_NULL;

        case ERR_NOMEM:
            printf("\nInternal error: memory allocation failed in list_insert\n");
            return ERR_NULL;
                            
        case ERR_NODE_NULL:
            printf("\nInternal error: unexpected NULL pointer to the node %zu in list_insert\n", position);
            return ERR_NULL;
        
        default:
            break;
    }

    return ERR_OK;
}

int error_check_list_remove(int error_code, size_t position) {
    
    switch (error_code) {
                            
       case ERR_LIST_NULL:
            printf("\nInternal error: unexpected NULL List type pointer in list_remove\n");
            return ERR_NULL;
                            
        case ERR_NOSIZE:
            printf("\nInternal error: called list_remove on an empty list");
            return ERR_NULL;
        
        case ERR_POS:
            printf("\nInternal error: invalid parameter passed to list_remove (position > list_size)\n");
            return ERR_NULL;
                            
        case ERR_NODE_NULL:
            printf("\nInternal error: unexpected NULL pointer to the node %zu in list_remove\n", position);
            return ERR_NULL;
                            
        case ERR_NULL:
            printf("\nInternal error: invalid parameter passed to list_remove (iterator pointing to a node containing a NULL link)\n");
            return ERR_NULL;
        
        default:
            break;
    }

    return ERR_OK;
}