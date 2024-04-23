/**
 * @file allocator.h
 * @author Sasha P (aloxwastaken@gmail.com)
 * @brief The allocator module
 * @version 0.1
 * @date 2024-04-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

/*** Headers ***/
#include <stdint.h>

#include "allocator_status.h"

/*** Functions ***/

/**
 * @brief Allocates `bytes` amount of bytes into ptr
 * 
 * @param bytes The amount of bytes to allocate
 * @param[in,out] ptr The pointer which will store the allocated memory
 *
 * @return `allocator_status_t` - a status code 
 * @retval `SUCCESS` - Successfully allocated memory into `*ptr`
 * @retval `ALLOCATOR_MALLOC_INVALID_PARAMETERS` - one of the parameters was invalid
 * @retval `ALLOCATOR_MALLOC_OUT_OF_MEMORY` - cannot allocate anymore, out of memory
*/
allocator_status_t ALLOCATOR_malloc(size_t bytes, void** ptr);

/**
 * @brief Frees the allocated memory in `*ptr`
 * 
 * @param[in,out] ptr The pointer to free and set to NULL right after
 * 
 * @return `allocator_status_t` - a status code 
 * @retval `ALLOCATOR_FREE_INVALID_PARAMETERS` - one of the parameters was invalid
 * @retval `ALLOCATOR_FREE_INVALID_POINTER` - invalid pointer has been passed
*/
allocator_status_t ALLOCATOR_free(void** ptr);

/**
 * @brief Prints the the screen the allocated chunks with information
*/
void ALLOCATOR_dump_allocated_chunks();

/**
 * @brief Prints the the screen the freed chunks with information
*/
void ALLOCATOR_dump_freed_chunks();

#endif /* __ALLOCATOR_H__ */
