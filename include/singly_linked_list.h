/**
*
*   @file singly_linked_list.h
*  
*   @brief Public API for the singly_linked_list module.
*
*   @details Module to create and manage a singly linked list implementing a struct
*   iterator for traversal logic and dynamic memory allocation.
*
*   Both the list and the iterator struct are opaque and traversal logic is hidden
*   from the caller to hide data structure internal representation.
*
*/

#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stdio.h>

typedef struct Iterator It;

typedef struct List List;

enum list_error {
    ERR_OK = 0,
    ERR_LIST_NULL = -1,
    ERR_IT_NULL = -2,
    ERR_NODE_NULL = -3,
    ERR_NOMEM = -4,
    ERR_NOSIZE = -5,
    ERR_POS = -6,
    ERR_NULL = -7
};

/**
*   @brief  Creates the list and the nodes integrating dynamic memory, links and initializes
*           every node, handles allocation failure and prevents memory leaks.
*
*   @param  list_size       Number of nodes
*   @param  **list_ptr      Address of the pointer to allocate the memory of the list container
*
*   @retval ERR_NOSIZE      If list_size is 0
*   @retval ERR_NULL        If **list_ptr is NULL
*   @retval ERR_NOMEM       If memory allocation fails
*   @retval ERR_OK          If no errors occurred
*
*   @pre    **list_ptr != NULL
*   @pre    list_size != 0
*   @post   If allocation fails the memory of all previous nodes and the list container is freed
*   @post   If passed parameters are invalid memory is not allocated and *list_ptr is left unchanged
*   @post   On success the memory of a number of nodes equal to list_size and of the list container is allocated and assigned to *list_ptr
*   @post   On success every node data field is initialized to 0
*   @post   On success the caller owns the memory of the list and is responsible to free it using list_delete
*   
*   @par    Invariants:
*
*           -the size field in the list container always matches the number of nodes
*
*           -the head link in the list container always points to the first node
*
*           -the link in each node points to the next node and the tail is NULL
*
*/
int list_create(size_t list_size, List** list_ptr);

/**
*   @brief  Deletes the list and all the nodes by freeing dynamic memory.
*
*   @param  **list_ptr      Address of the pointer to the list container
*
*   @retval ERR_NULL        If **list_ptr is NULL
*   @retval ERR_LIST_NULL   If *list_ptr is NULL
*   @retval ERR_OK          If no errors occurred
*
*   @pre    list_create must have been called
*   @pre    **list_ptr != NULL
*   @pre    *list_ptr != NULL
*   @post   If passed parameter is invalid memory is not freed and *list_ptr is left unchanged
*   @post   On success the memory of every node and the list container is freed and *list_ptr is set to NULL
*
*/
int list_delete(List** list_ptr);

/**
*   @brief  Assigns the size of the list to a variable.
*
*   @param  *list_ptr       Pointer to the list container
*   @param  *list_size      Address of the variable to store the size of the list
*
*   @retval ERR_LIST_NULL   If *list_ptr is NULL
*   @retval ERR_NULL        If *list_size is NULL
*   @retval ERR_OK          If no errors occurred
*
*   @pre    list_create must have been called
*   @pre    *list_ptr != NULL
*   @pre    *list_size != NULL
*   @post   If passed parameters are invalid list_size is left unchanged
*   @post   On success the size field hold in the list container is assigned to list_size
*
*/
int list_getsize(List* list_ptr, size_t* list_size);

/**
*   @brief  Creates the iterator integrating dynamic memory and handles allocation failure.
*
*   @param  **it_ptr        Address of the pointer to allocate the memory of the iterator
*
*   @retval ERR_IT_NULL     If **it_ptr is NULL
*   @retval ERR_NOMEM       If memory allocation fails
*   @retval ERR_OK          If no errors occurred
*
*   @pre    **it_ptr != NULL
*   @pre    If passed parameter is invalid memory is not allocated and *it_ptr is left unchanged
*   @post   If allocation fails *it_ptr is left unchanged
*   @post   On success the memory of the iterator is allocated and assigned to *it_ptr
*   @post   On success the iterator is set to NULL
*   @post   On success the caller owns the memory of the iterator and is responsible to free it using iterator_delete       
*
*/
int iterator_create(It** it_ptr);

/**
*   @brief  Deletes the iterator by freeing dynamic memory.
*
*   @param  **it_ptr        Address of the pointer to the iterator
*
*   @retval ERR_NULL        If **it_ptr is NULL
*   @retval ERR_IT_NULL     If *it_ptr is NULL
*   @retval ERR_OK          If no errors occurred
*
*   @pre    iterator_create must have been called
*   @pre    **it_ptr != NULL
*   @pre    *it_ptr != NULL
*   @post   If passed parameter is invalid memory is not freed and *it_ptr is left unchanged
*   @post   On success the memory of the iterator is freed and *it_ptr is set to NULL
*
*/
int iterator_delete(It** it_ptr);

/**
*   @brief  Assigns the head to the iterator.
*
*   @param  *list_ptr       Pointer to the list container
*   @param  *it_ptr         Pointer to the iterator
* 
*   @retval ERR_LIST_NULL   If *list_ptr is NULL
*   @retval ERR_IT_NULL     If *it_ptr is NULL
*   @retval ERR_OK          If no errors occurred
*
*   @pre    iterator_create must have been called
*   @pre    *list_ptr != NULL
*   @pre    *it_ptr != NULL
*   @post   If passed parameters are invalid the iterator is left unchanged
*   @post   On success the head link is assigned to the iterator
*
*/
int iterator_tohead(List* list_ptr, It* it_ptr);

/**
*   @brief  Assigns the link of the next node to the iterator.
* 
*   @param  *it_ptr         Pointer to the iterator
* 
*   @retval ERR_IT_NULL     If *it_ptr is NULL
*   @retval ERR_NULL        If the iterator is NULL
*   @retval ERR_OK          If no errors occurred
*
*   @pre    list_create, iterator_create and iterator_tohead must have been called
*   @pre    *it_ptr != NULL
*   @pre    The iterator must not be NULL
*   @post   If passed parameter is invalid or the iterator is NULL the iterator is left unchanged
*   @post   On success the link to the next node where the iterator was is assigned to the iterator
* 
*/
int iterator_tonext(It* it_ptr);

/**
*   @brief  Assigns the link of the node at a position to the iterator.
*
*   @param  *list_ptr       Pointer to the list container
*   @param  *it_ptr         Pointer to the iterator
*   @param  position        Variable holding the position of the node
* 
*   @retval ERR_LIST_NULL   If *list_ptr is NULL
*   @retval ERR_IT_NULL     If *it_ptr is NULL
*   @retval ERR_POS         If position is 0 or higher than the size of the list + 1
*   @retval ERR_OK          If no errors occurred
*
*   @pre    list_create and iterator_create must have been called
*   @pre    *list_ptr != NULL
*   @pre    *it_ptr != NULL
*   @pre    0 < position <= size of the list + 1
*   @post   If passed parameters are invalid the iterator is left unchanged
*   @post   On success the link of the node at position is assigned to the iterator
*
*   @note   The tail can be assigned to the iterator to append a new node at the end of the list
* 
*/
int iterator_topos(List* list_ptr, It* it_ptr, size_t position);

/**
*   @brief  Extracts the data of the node at the position of the iterator.
*
*   @param  *it_ptr         Pointer to the iterator
*   @param  *node_data      Address of the variable to store the data of the node
* 
*   @retval ERR_IT_NULL     If *it_ptr is NULL
*   @retval ERR_NODE_NULL   If the iterator is NULL
*   @retval ERR_NULL        If *node_data is NULL
*   @retval ERR_OK          If no errors occurred
*
*   @pre    list_create, iterator_create and iterator_tohead must have been called
*   @pre    *it_ptr != NULL
*   @pre    *node_data != NULL
*   @pre    The iterator must not be NULL
*   @post   If passed parameters are invalid node_data is left unchanged
*   @post   On success the data of the node at the position of the iterator is assigned to node_data
* 
*/
int iterator_getdata(It* it_ptr, int* node_data);

/**
*   @brief  Assigns data to the node at the position of the iterator.
*
*   @param  *it_ptr         Pointer to the iterator
*   @param  node_data       Variable holding the data to assign to the node
* 
*   @retval ERR_IT_NULL     If *it_ptr is NULL
*   @retval ERR_NODE_NULL   If the iterator is NULL
*   @retval ERR_OK          If no errors occurred
*
*   @pre    list_create, iterator_create and iterator_tohead must have been called
*   @pre    *it_ptr != NULL
*   @pre    The iterator must not be NULL
*   @post   If passed parameters are invalid the node data is left unchanged
*   @post   On success the data from node_data is assigned at the node at the position of the iterator
* 
*/
int iterator_setdata(It* it_ptr, int node_data);

/**
*   @brief  Checks if the iterator is NULL.
*
*   @param  *it_ptr         Pointer to the iterator
* 
*   @retval ERR_IT_NULL     If *it_ptr is NULL
*   @retval ERR_NODE_NULL   If the iterator is NULL
*   @retval ERR_OK          If no errors occurred
*
*   @pre    list_create, iterator_create and iterator_tohead must have been called
*   @pre    *it_ptr != NULL
*   @post   On success returns either ERR_NODE_NULL or ERR_OK
*
*   @note   For the purpose of this function the iterator is not required to not be NULL
* 
*/
int iterator_isnull(It* it_ptr);

/**
*   @brief  Creates a new node and inserts it in the list.
*
*   @param  *list_ptr       Pointer to the list container
*   @param  node_data       Variable holding the data to assign to the node
*   @param  position        Variable holding the position where to insert the node
* 
*   @retval ERR_LIST_NULL   If *list_ptr is NULL
*   @retval ERR_POS         If position is larger than the size of the list + 1
*   @retval ERR_NOMEM       If memory allocation failed
*   @retval ERR_NODE_NULL   If the iterator is NULL
*   @retval ERR_OK          If no errors occurred
*
*   @pre    list_create and iterator_create must have been called
*   @pre    *list_ptr != NULL
*   @pre    0 < position <= size of the list + 1
*   @post   If passed parameters are invalid memory is not allocated and the list is left unchanged
*   @post   If allocation fails the list is left unchanged
*   @post   If position > 1 and the iterator is NULL or iterator_topos fails the memory of the new node is freed
*   @post   On success the memory of the new node is allocated and assigned to the link at position
*   @post   On success the link of the next node is assigned to the new node
*   @post   On success the size field in the list container is increased by 1
*
*   @note   Position can be equal to the size of the list + 1 to append a new node at the end of the list
*   @note   Head can be NULL to insert the first node at the beginning of the list
*
*   @par    Invariants:
*
*               -the invariant where the size field in the list container matches the number of nodes is preserved
*
*               -the invariant where the head link in the list container always points to the first node is preserved
*
*               -the invariant the link in each node points to the next node and the tail is NULL is preserved
* 
*/
int list_insert(List* list_ptr, int node_data, size_t position);

/**
*   @brief  Removes a node from the list by freeing dynamic memory.
*
*   @param  *list_ptr       Pointer to the list container
*   @param  position        Variable holding the position of the node to remove
* 
*   @retval ERR_LIST_NULL   If *list_ptr is NULL
*   @retval ERR_NOSIZE      If the size field in the list container is 0
*   @retval ERR_POS         If position is larger than the size of the list
*   @retval ERR_NODE_NULL   If the iterator is NULL
*   @retval ERR_NULL        If the link in the node at the position of the iterator is NULL
*   @retval ERR_OK          If no errors occurred
*
*   @pre    list_create and iterator_create must have been called
*   @pre    *list_ptr != NULL
*   @pre    The size field in the list container must be more than 0
*   @pre    0 < position <= size of the list
*   @post   If passed parameters are invalid the memory of the node is not freed and the list is left unchanged
*   @post   If position > 1 and iterator_topos fails the memory of the node is not freed and the list is left unchanged
*   @post   If position > 1 and the iterator is NULL the memory of the node is not freed and the list is left unchanged 
*   @post   If position > 1 and the link in the node at the iterator position is NULL the memory of the node is not freed and the list is left unchanged
*   @post   On success the memory of the node is freed
*   @post   On success the link of the next node is assigned to the previous node
*   @post   On success the size field in the list container is decreased by 1
*
*   @note   If list invariants were mainteined before calling this function then head can not be NULL if the size field in the list container is more than 0
*
*   @par    Invariants:
*
*               -the invariant where the size field in the list container matches the number of nodes is preserved
*
*               -the invariant where the head link in the list container always points to the first node is preserved
*
*               -the invariant the link in each node points to the next node and the tail is NULL is preserved
* 
*/
int list_remove(List* list_ptr, size_t position);

#endif
