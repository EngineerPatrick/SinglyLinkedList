/**
*
*   @file singly_linked_list.c
*  
*   @brief Implementation of the singly_linked_list module.
*
*   @details Contains the opaque structs, the internal node
*   definition and the logic for list operations.
*
*/

#include <stdlib.h>
#include "singly_linked_list.h"

typedef struct Node Node;

struct List {
    size_t size;
    Node* head;
};

struct Node {
    int data;
    Node* link;
};

struct Iterator {
    Node* current;
};

static int list_memory(List** list_ptr, int option) {
    List* list_memory = NULL;

    if (option == 1) {
        list_memory =  malloc(sizeof(*list_memory));

        if (list_memory == NULL) {
            return ERR_NOMEM;
        }

        *list_ptr = list_memory;
    }

    else {
        free(*list_ptr);
        *list_ptr = NULL;
    }
    
    return ERR_OK;
}

static int iterator_memory(It** it_ptr, int option) {
    It* it_memory = NULL;

    if (option == 1) {
        it_memory =  malloc(sizeof(*it_memory));

        if (it_memory == NULL) {
            return ERR_NOMEM;
        }

        *it_ptr = it_memory;
    }

    else {
        free(*it_ptr);
        *it_ptr = NULL;
    }

    return ERR_OK;
}

static int node_memory(Node** node_ptr, int option) {
    Node* node_memory = NULL;

    if (option == 1) {
        node_memory =  malloc(sizeof(*node_memory));

        if (node_memory == NULL) {
            return ERR_NOMEM;
        }

        *node_ptr = node_memory;
    }

    else {
        free(*node_ptr);
        *node_ptr = NULL;
    }

    return ERR_OK;
}

int list_create(size_t list_size, List** list_ptr) {  
    Node* prev_link = NULL;
    Node* node_ptr = NULL;

    int error_code = 0;

    if (list_size == 0) {
        return ERR_NOSIZE;
    }
    
    if (list_ptr == NULL) {
        return ERR_NULL;
    }

    error_code = list_memory(list_ptr, 1);

    if (error_code != ERR_OK) {
        return error_code;
    }

    (*list_ptr)->size = 0;
    (*list_ptr)->head = NULL;

    for (size_t position = 1; position <= list_size; position++) {
        error_code = node_memory(&node_ptr, 1);

        if (error_code != ERR_OK) {
            error_code = list_delete(list_ptr);

            if (error_code != ERR_OK) {
                return error_code;
            }

            return ERR_NOMEM;
        }
        
        node_ptr->data = 0;
        node_ptr->link = NULL;

        if (position == 1) {
            (*list_ptr)->head = node_ptr;
            prev_link = (*list_ptr)->head;
        }

        else {
            prev_link->link = node_ptr;
            prev_link = prev_link->link;
        }

        (*list_ptr)->size++;
    }

    return ERR_OK;
}

int list_delete(List** list_ptr) {
    Node* next_link = NULL;
    
    if (list_ptr == NULL) {
        return ERR_NULL;
    }

    if (*list_ptr == NULL) {
        return ERR_LIST_NULL;
    }

    while ((*list_ptr)->head != NULL) {
        next_link = (*list_ptr)->head->link;
        node_memory(&((*list_ptr)->head), 2);
        (*list_ptr)->head = next_link;
    }

    list_memory(list_ptr, 2);
    return ERR_OK;
}

int list_getsize(List* list_ptr, size_t* list_size) {

    if (list_ptr == NULL) {
        return ERR_LIST_NULL;
    }

    if (list_size == NULL) {
        return ERR_NULL;
    }

    *list_size = list_ptr->size;
    return ERR_OK;
}

int iterator_create(It** it_ptr) {
    int error_code = 0;

    if (it_ptr == NULL) {
        return ERR_NULL;
    }
    
    error_code = iterator_memory(it_ptr, 1);

    if (error_code != ERR_OK) {
        return ERR_NOMEM;
    }

    (*it_ptr)->current = NULL;
    return ERR_OK;
}

int iterator_delete(It** it_ptr) {

    if (it_ptr == NULL) {
        return ERR_NULL;
    }

    if (*it_ptr == NULL) {
        return ERR_IT_NULL;
    }

    iterator_memory(it_ptr, 2);
    return ERR_OK;
}

int iterator_tohead(List* list_ptr, It* it_ptr) {

    if (list_ptr == NULL) {
        return ERR_LIST_NULL;
    }

    if (it_ptr == NULL) {
        return ERR_IT_NULL;
    }

    it_ptr->current = list_ptr->head;
    return ERR_OK;  
}

int iterator_tonext(It* it_ptr) {
    
    if (it_ptr == NULL) {
        return ERR_IT_NULL;
    }

    if (it_ptr->current == NULL) {
        return ERR_NODE_NULL;
    }

    it_ptr->current = it_ptr->current->link;
    return ERR_OK;  
}

int iterator_topos(List* list_ptr, It* it_ptr, size_t position) {
    int error_code = 0;
    
    if (list_ptr == NULL) {
        return ERR_LIST_NULL;
    }
    
    if (it_ptr == NULL) {
        return ERR_IT_NULL;
    }

    if (position == 0 || position > list_ptr->size + 1) {
        return ERR_POS;
    }

    error_code = iterator_tohead(list_ptr, it_ptr);

    if (error_code != ERR_OK) {
        return error_code;
    }

    for (size_t i = 1; i < position; i++) {
        error_code = iterator_tonext(it_ptr);

        if (error_code != ERR_OK) {
            return error_code;
        }
    }

    return ERR_OK;
}

int iterator_getdata(It* it_ptr, int* node_data) {

    if (it_ptr == NULL) {
        return ERR_IT_NULL;
    }

    if (it_ptr->current == NULL) {
        return ERR_NODE_NULL;
    }

    if (node_data == NULL) {
        return ERR_NULL;
    }

    *node_data = it_ptr->current->data;
    return ERR_OK;
}

int iterator_setdata(It* it_ptr, int node_data) {

    if (it_ptr == NULL) {
        return ERR_IT_NULL;
    }

    if (it_ptr->current == NULL) {
        return ERR_NODE_NULL;
    }

    it_ptr->current->data = node_data;
    return ERR_OK;
}

int iterator_isnull(It* it_ptr) {

    if (it_ptr == NULL) {
        return ERR_IT_NULL;
    }

    if (it_ptr->current == NULL) {
        return ERR_NODE_NULL;
    }

    return ERR_OK;
}

int list_insert(List* list_ptr, int node_data, size_t position) {
    Node* next_link = NULL;
    Node* node_ptr = NULL;
    It it = {.current = NULL};
    It* it_ptr = &it;

    int error_code = 0;

    if (list_ptr == NULL) {
        return ERR_LIST_NULL;
    }

    if (position > list_ptr->size + 1 || position == 0) {
        return ERR_POS;
    }

    error_code = node_memory(&node_ptr, 1);

    if (error_code != ERR_OK) {
        return ERR_NOMEM;
    }

    if (position == 1) {
        next_link = list_ptr->head;
        list_ptr->head = node_ptr;
    }

    else {
        error_code = iterator_topos(list_ptr, it_ptr, position - 1);

        if (error_code != ERR_OK) {
            node_memory(&node_ptr, 2);
            return error_code;
        }

        if (it_ptr->current == NULL) {
            node_memory(&node_ptr, 2);
            return ERR_NODE_NULL;
        }

        next_link = it_ptr->current->link;
        it_ptr->current->link = node_ptr;
    }

    node_ptr->link = next_link;
    node_ptr->data = node_data;
    list_ptr->size++;
    return ERR_OK;
}

int list_remove(List* list_ptr, size_t position) {
    Node* next_link = NULL;
    It it = {.current = NULL};
    It* it_ptr = &it;

    int error_code = 0;

    if (list_ptr == NULL) {
        return ERR_LIST_NULL;
    }

    if (list_ptr->size == 0) {
        return ERR_NOSIZE;
    }

    if (position > list_ptr->size || position == 0) {
        return ERR_POS;
    }

    if (position == 1) {
        next_link = list_ptr->head->link;
        node_memory(&(list_ptr->head), 2);
        list_ptr->head = next_link;
    }

    else {
        error_code = iterator_topos(list_ptr, it_ptr, position - 1);

        if (error_code != ERR_OK) {
            return error_code;
        }

        if (it_ptr->current == NULL) {
            return ERR_NODE_NULL;
        }

        if (it_ptr->current->link == NULL) {
            return ERR_NULL;
        }
        
        next_link = it_ptr->current->link->link;
        node_memory(&(it_ptr->current->link), 2);
        it_ptr->current->link = next_link;
    }

    list_ptr->size--;
    return ERR_OK;
}