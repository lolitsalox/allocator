/**
 * @file main.c
 * @author Sasha P (aloxwastaken@gmail.com)
 * @brief The main file of the allocator project
 * @version 0.1
 * @date 2024-04-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/*** Headers ***/
#include <stdio.h>

#include "allocator/allocator.h"

/*** Functions ***/
int main(void)
{
    allocator_status_t status = ALLOCATOR_STATUS_UNINITIALIZED;
    void* ptr = NULL;
    size_t index = 0;

    for (index = 0; index < 11; ++index) 
    {
        status = ALLOCATOR_malloc(index, &ptr);
        if (ALLOCATOR_STATUS_SUCCESS != status) {
            goto l_cleanup;
        }

        if (!(index % 3) || !(index % 4))
        {
            status = ALLOCATOR_free(&ptr);
            if (ALLOCATOR_STATUS_SUCCESS != status) {
                goto l_cleanup;
            }
        }
    }

    ALLOCATOR_dump_allocated_chunks();
    ALLOCATOR_dump_freed_chunks();

l_cleanup:
    return (int)status;
}
