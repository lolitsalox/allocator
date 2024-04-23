/**
 * @file allocator.c
 * @author Sasha P (aloxwastaken@gmail.com)
 * @brief The allocator module
 * @version 0.1
 * @date 2024-04-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/*** Headers ***/
#include <stdio.h>
#include <assert.h>

#include "allocator_internal.h"
#include "allocator.h"

/*** Functions ***/
allocator_status_t ALLOCATOR_malloc(size_t bytes, void** ptr)
{
    allocator_status_t status = ALLOCATOR_STATUS_UNINITIALIZED;
    
    size_t index = 0;
    size_t tail_size = 0;
    
    Chunk chunk = { 0 };
    void* temp_ptr = NULL;

    if (NULL == ptr)
    {
        status = ALLOCATOR_STATUS_ALLOCATOR_MALLOC_INVALID_PARAMETERS;
        goto l_cleanup;
    }

    /* If there is need to allocated */
    if (0 != bytes)
    {
        for (index = 0; index < g_freed_chunks.count; ++index)
        {
            chunk = g_freed_chunks.chunks[index];
            if (bytes > chunk.size)
            {
                continue;
            }

            allocator_remove_chunk(&g_freed_chunks, index);
            tail_size = chunk.size - bytes;

            allocator_insert_chunk(&g_allocated_chunks, chunk.start, bytes);
            allocator_insert_chunk(&g_freed_chunks, chunk.start + bytes, tail_size);

            temp_ptr = chunk.start;
            break;
        }
    }

    if (MAX_CHUNKS == index)
    {
        status = ALLOCATOR_STATUS_ALLOCATOR_MALLOC_OUT_OF_MEMORY;
        goto l_cleanup;
    }

    *ptr = temp_ptr;
    status = ALLOCATOR_STATUS_SUCCESS;

l_cleanup:
    return status;
}

allocator_status_t ALLOCATOR_free(void** ptr)
{
    allocator_status_t status = ALLOCATOR_STATUS_UNINITIALIZED;
    Chunk chunk = { 0 };
    int32_t found_index = 0;

    if (NULL == ptr)
    {
        status = ALLOCATOR_STATUS_ALLOCATOR_FREE_INVALID_PARAMETERS;
        goto l_cleanup;
    }

    if (NULL != *ptr)
    {
        found_index = allocator_find_chunk(g_allocated_chunks, *ptr);
        if (-1 == found_index)
        {
            status = ALLOCATOR_STATUS_ALLOCATOR_FREE_INVALID_POINTER;
            goto l_cleanup;
        }

        chunk = g_allocated_chunks.chunks[found_index];

        allocator_remove_chunk(&g_allocated_chunks, found_index);
        allocator_insert_chunk(&g_freed_chunks, chunk.start, chunk.size);

        allocator_merge_chunks(&g_freed_chunks);
    }

    *ptr = NULL;
    status = ALLOCATOR_STATUS_SUCCESS;

l_cleanup:
    return status;
}

void ALLOCATOR_dump_allocated_chunks()
{
    (void)puts("Allocated chunks:");
    allocator_dump_chunks(g_allocated_chunks);
}

void ALLOCATOR_dump_freed_chunks()
{
    (void)puts("Freed chunks:");
    allocator_dump_chunks(g_freed_chunks);
}

void allocator_dump_chunks(ChunkList chunk_list)
{
    Chunk chunk = { 0 };
    size_t index = 0;

    for (index = 0; index < chunk_list.count; ++index)
    {
        chunk = chunk_list.chunks[index];
        (void)printf("\t(%02zu) size: %5zu, start: %p\n", index, chunk.size, chunk.start);
    }

    (void)puts("");
}

int32_t allocator_find_chunk(ChunkList chunk_list, void* ptr)
{
    size_t index = 0;
    int32_t found_index = -1;

    for (index = 0; index < chunk_list.count; ++index)
    {
        if (ptr == chunk_list.chunks[index].start)
        {
            found_index = index;
            break;
        }
    }

    return found_index;
}

void allocator_insert_chunk(ChunkList* chunk_list, void* start, size_t size)
{
    int32_t index = 0;
    Chunk temp_chunk = { 0 };
    Chunk* chunk = NULL;

    if (0 == size)
    {
        return;
    }

    assert(chunk_list->count < MAX_CHUNKS);

    chunk = &chunk_list->chunks[chunk_list->count];

    chunk->start = start;
    chunk->size = size;

    for (index = chunk_list->count; 
        (index > 0) &&
        (chunk_list->chunks[index].start < chunk_list->chunks[index - 1].start);
        --index)
    {
        /* Swapping chunks */
        temp_chunk = chunk_list->chunks[index];
        chunk_list->chunks[index] = chunk_list->chunks[index - 1];
        chunk_list->chunks[index - 1] = temp_chunk;    
    }

    ++chunk_list->count;
}

void allocator_remove_chunk(ChunkList* chunk_list, int32_t chunk_index)
{
    /* chunk_list->count may be 0 and then underflow if its unsigned */
    int32_t index = 0;

    for (index = chunk_index; index < (long long)chunk_list->count - 1; ++index)
    {
        chunk_list->chunks[index] = chunk_list->chunks[index + 1];
    }

    --chunk_list->count;
}

void allocator_merge_chunks(ChunkList* chunk_list)
{
    /* chunk_list->count may be 0 and then underflow if its unsigned */
    int32_t index = 0;
    Chunk* current_chunk = NULL;
    Chunk next_chunk = { 0 };

    for (index = 0; index < (long long)chunk_list->count - 1; ++index)
    {
        current_chunk = &chunk_list->chunks[index];
        next_chunk = chunk_list->chunks[index + 1];

        /* If the end of the current chunk is the start of the next chunk,
         * merge them. */
        if (current_chunk->start + current_chunk->size == next_chunk.start)
        {
            /* Setting the new size */
            current_chunk->size += next_chunk.size;

            /* Removes the next chunk */
            allocator_remove_chunk(chunk_list, index + 1);
        }
    }
}
