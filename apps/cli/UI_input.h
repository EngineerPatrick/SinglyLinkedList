/**
*
*   @file UI_input.h   
*
*   @brief Public API for the UI_inpt module.
*
*   @details User interface module to input the size of the list, the data of
*   the nodes and a specific position in the list.
*   
*   Handles and output invalid input errors. 
*
*/

#ifndef UI_INPUT_H
#define UI_INPUT_H

#include <stdio.h>

enum input_error {
    INERR_VALID = 0,
    INERR_FGETS = -1,
    INERR_OVERFLOW = -2,
    INERR_RANGE = -3,
    INERR_INVALID = -4,
    INERR_PARAM = -5,
    INERR_POS = -6,
    INERR_NULL = -7,
    INERR_NOSIZE = -8
};

/**
*   @brief  Handles the input of the size of the list.
*
*   @param  upper_bound     Largest size of the list accepted
*   @param  *list_size      Address of the variable to store the input
*
*   @retval INERR_PARAM       If upper_bound is 0
*   @retval INERR_NULL        If *list_size is NULL
*   @retval INERR_FGETS       If fgets fails
*   @retval INERR_VALID       If no errors occurred
*
*   @pre    upper_bound > 0
*   @pre    *list_size != NULL
*   @post   If passed parameters are invalid then lsit_size is left unchanged
*   @post   If fgets fails then list_size is left unchanged
*   @post   On success the input is assigned to list_size
*
*/
int input_size(size_t upper_bound, size_t* list_size);

/**
*   @brief  Handles the input of the data of a node.
*
*   @param  position        Position of the node to store the input data
*   @param  lower_bound     Lowhest integer accepted
*   @param  upper_bound     Highest integer accepted
*   @param  option          1 if called during t creation, 2 if called during node insertion, any other number if called during data search
*   @param  *node_data      Address of the variable to store the input
*
*   @retval INERR_POS         If position is 0
*   @retval INERR_PARAM       If lower_bound > upper_bound
*   @retval INERR_NULL        If *node_data is NULL
*   @retval INERR_FGETS       If fgets fails
*   @retval INERR_VALID       If no errors occurred
*
*   @pre    position > 0
*   @pre    lower_bound < upper_bound
*   @pre    *node_data != NULL
*   @post   If passed parameters are invalid then node_data is left unchanged
*   @post   If fgets fails then node_data is left unchanged
*   @post   On success the input is assigned to node_data
*
*/
int input_data(size_t position, int lower_bound, int upper_bound, int option, int* node_data);

/**
*   @brief  Handles the input of the position of a node.
*
*   @param  list_size       Variable holding the size of the list
*   @param  option          1 if called during node insertion, any other number if called during node deletion
*   @param  *position       Variable holding the size of the list
*
*   @retval INERR_NOSIZE      If list_size is 0
*   @retval INERR_NULL        If *position is NULL
*   @retval INERR_FGETS       If fgets fails
*   @retval INERR_VALID       If no errors occurred
*
*   @pre    list_size > 0
*   @pre    *position != NULL
*   @post   If passed parameters are invalid then position is left unchanged
*   @post   If fgets fails then position is left unchanged
*   @post   On success the input is assigned to position
*
*/
int input_position(size_t list_size, int option, size_t* position);

/**
*   @brief  Handles error cases during the input of the size of the list.
*
*   @param  upper_bound     Highest size of the list accepted
*   @param  *input          Address of the variable to store the input
*
*   @retval INERR_PARAM       If upper_bound is 0
*   @retval INERR_NULL        If *input is NULL
*   @retval INERR_FGETS       If fgets fails
*   @retval INERR_RANGE       If input is out of range
*   @retval INERR_OVERFLOW    If input is too long and the buffer overflows
*   @retval INERR_INVALID     If input contains a non-numerical character
*   @retval INERR_VALID       If no errors occurred
*
*   @pre    upper_bound > 0
*   @pre    *input != NULL
*   @post   If passed parameters are invalid then input is left unchanged
*   @post   If fgets fails then input is left unchanged
*   @post   If the input is out of range then input is left unchanged and stdin is flushed
*   @post   If the the buffer overflows then input is left unchanged
*   @post   If th input contains a non-numerical character then input is left unchanged
*   @post   On success the input is assigned to input
*
*/
int error_check_size(size_t upper_bound, size_t* input);

/**
*   @brief  Handles error cases during the input of the data of a node or the UI option.
*
*   @param  lower_bound     Lowest integer accepted
*   @param  upper_bound     Highest integer accepted
*   @param  *input          Address of the variable to store the input
*
*   @retval INERR_PARAM       If lower_bound > upper_bound
*   @retval INERR_NULL        If *input is NULL
*   @retval INERR_FGETS       If fgets fails
*   @retval INERR_OVERFLOW    If input is too long and the buffer overflows
*   @retval INERR_RANGE       If input is out of range
*   @retval INERR_INVALID     If input contains a non-numerical character
*   @retval INERR_VALID       If no errors occurred
*
*   @pre    lower_bound < upper_bound
*   @pre    *input != NULL
*   @post   If passed parameters are invalid then input is left unchanged
*   @post   If fgets fails then input is left unchanged
*   @post   If the the buffer overflows then input is left unchanged and stdin is flushed
*   @post   If the input is out of range then input is left unchanged
*   @post   If th input contains a non-numerical character then input is left unchanged
*   @post   On success the input is assigned to input
*
*/
int error_check_data(int lower_bound, int upper_bound, int* input);

#endif
