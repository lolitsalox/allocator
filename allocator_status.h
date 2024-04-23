/**
 * @file allocator_status.h
 * @author Sasha P (aloxwastaken@gmail.com)
 * @brief Statuses for the allocator project
 * @version 0.1
 * @date 2024-04-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __ALLOCATOR_STATUS_H__
#define __ALLOCATOR_STATUS_H__

/*** Enums ***/
typedef enum {
    ALLOCATOR_STATUS_UNINITIALIZED = -1,
    ALLOCATOR_STATUS_SUCCESS = 0,
    ALLOCATOR_STATUS_ALLOCATOR_MALLOC_INVALID_PARAMETERS,
    ALLOCATOR_STATUS_ALLOCATOR_MALLOC_OUT_OF_MEMORY,
    ALLOCATOR_STATUS_ALLOCATOR_FREE_INVALID_PARAMETERS,
    ALLOCATOR_STATUS_ALLOCATOR_FREE_INVALID_POINTER,
} allocator_status_t;

#endif /* __ALLOCATOR_STATUS_H__ */