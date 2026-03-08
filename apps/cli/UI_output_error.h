/**
*
*   @file UI_output_error.h
*
*   @brief Public API for the UI_output_error module.
*
*   @details Error output module. Designed to output errors from
*   the singly_linked_list module API.
*
*/

#ifndef UI_OUTPUT_ERROR_H
#define UI_OUTPUT_ERROR_H

/**
*   @brief  Outputs the error cases when list_create is called.
*
*   @param  error_code      Integer returned from list_create
*
*   @retval ERR_NULL        On any error case
*   @retval ERR_OK          If no error occurred
*
*   @pre    list_create must have been called
*   @post   The error case is printed
*
*/
int error_check_list_create(int error_code);

/**
*   @brief  Outputs the error cases when list_delete is called.
*
*   @param  error_code      Integer returned from list_delete
*
*   @retval ERR_NULL        On any error case
*   @retval ERR_OK          If no error occurred
*
*   @pre    list_delete must have been called
*   @post   The error case is printed
*
*/
int error_check_list_delete(int error_code);

/**
*   @brief  Outputs the error cases when list_getsize is called.
*
*   @param  error_code      Integer returned from list_getsize
*
*   @retval ERR_NULL        On any error case
*   @retval ERR_OK          If no error occurred
*
*   @pre    list_getsize must have been called
*   @post   The error case is printed
*
*/
int error_check_list_getsize(int error_code);

/**
*   @brief  Outputs the error cases when iterator_create is called.
*
*   @param  error_code      Integer returned from iterator_create
*
*   @retval ERR_NULL        On any error case
*   @retval ERR_OK          If no error occurred
*
*   @pre    iterator_create must have been called
*   @post   The error case is printed
*
*/
int error_check_iterator_create(int error_code);

/**
*   @brief  Outputs the error cases when iterator_delete is called.
*
*   @param  error_code      Integer returned from iterator_delete
*
*   @retval ERR_NULL        On any error case
*   @retval ERR_OK          If no error occurred
*
*   @pre    iterator_delete must have been called
*   @post   The error case is printed
*
*/
int error_check_iterator_delete(int error_code);

/**
*   @brief  Outputs the error cases when iterator_tohead is called.
*
*   @param  error_code      Integer returned from iterator_tohead
*
*   @retval ERR_NULL        On any error case
*   @retval ERR_OK          If no error occurred
*
*   @pre    iterator_tohead must have been called
*   @post   The error case is printed
*
*/
int error_check_iterator_tohead(int error_code);

/**
*   @brief  Outputs the error cases when iterator_tonext is called.
*
*   @param  error_code      Integer returned from iterator_tonext
*   @param  position        position of the node
*
*   @retval ERR_NULL        On any error case
*   @retval ERR_OK          If no error occurred
*
*   @pre    iterator_tonext must have been called
*   @post   The error case is printed
*
*/
int error_check_iterator_tonext(int error_code, size_t position);

/**
*   @brief  Outputs the error cases when iterator_getdata is called.
*
*   @param  error_code      Integer returned from iterator_getdata
*   @param  position        position of the node
*
*   @retval ERR_NULL        On any error case
*   @retval ERR_OK          If no error occurred
*
*   @pre    iterator_getdata must have been called
*   @post   The error case is printed
*
*/
int error_check_iterator_getdata(int error_code, size_t position);

/**
*   @brief  Outputs the error cases when iterator_setdata is called.
*
*   @param  error_code      Integer returned from terator_setdata
*   @param  position        position of the node
*
*   @retval ERR_NULL        On any error case
*   @retval ERR_OK          If no error occurred
*
*   @pre    iterator_setdata must have been called
*   @post   The error case is printed
*
*/
int error_check_iterator_setdata(int error_code, size_t position);

/**
*   @brief  Outputs the error cases when iterator_isnull is called.
*
*   @param  error_code      Integer returned from iterator_isnull
*
*   @retval ERR_NULL        On any error case
*   @retval ERR_OK          If no error occurred
*
*   @pre    iterator_isnull must have been called
*   @post   The error case is printed
*
*/
int error_check_iterator_isnull(int error_code);

/**
*   @brief  Outputs the error cases when list_insert is called.
*
*   @param  error_code      Integer returned from list_insert
*   @param  position        position of the node
*
*   @retval ERR_NULL        On any error case
*   @retval ERR_OK          If no error occurred
*
*   @pre    list_insert must have been called
*   @post   The error case is printed
*
*/
int error_check_list_insert(int error_code, size_t position);

/**
*   @brief  Outputs the error cases when list_remove is called.
*
*   @param  error_code      Integer returned from list_remove
*   @param  position        position of the node
*
*   @retval ERR_NULL        On any error case
*   @retval ERR_OK          If no error occurred
*
*   @pre    list_remove must have been called
*   @post   The error case is printed
*
*/
int error_check_list_remove(int error_code, size_t position);

#endif