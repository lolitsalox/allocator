/**
 * @file allocator_internal.h
 * @author Sasha P (aloxwastaken@gmail.com)
 * @brief The internal allocator module
 * @version 0.1
 * @date 2024-04-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __ALLOCATOR_INTERNAL_H__
#define __ALLOCATOR_INTERNAL_H__

/*** Headers ***/
#include <stdint.h>
#include <stdbool.h>

#include "allocator_status.h"

/*** Constants ***/
#define KILOBYTE 1024
#define MAX_CHUNKS 64

#define MAX_BUFFER_SIZE MAX_CHUNKS * KILOBYTE

/*** Structs ***/
typedef struct {
    void* start;
    size_t size;
} Chunk;

typedef struct {
    Chunk chunks[MAX_CHUNKS];
    size_t count;
} ChunkList;

/*** Globals ***/
uint8_t g_memory[MAX_BUFFER_SIZE] = { 0 };
ChunkList g_allocated_chunks = { 0 };
ChunkList g_freed_chunks = { 
    .chunks = { 
        {
            .start = &g_memory[0],
            .size = MAX_BUFFER_SIZE,
        }
    },
    .count = 1
 };

/*** Functions ***/

/**
 * @brief Prints to the screen the chunks within `chunk_list`
 * 
 * @param chunk_list The list of chunks to be printed
*/
void allocator_dump_chunks(ChunkList chunk_list);

/**
 * @brief Searches for the index of a chunk inside `chunk_list`
 * that has `ptr` as its start pointer.
 * 
 * @param chunk_list the chunk list to be searched
 * @param ptr the pointer to search for
 * @return int32_t an index to the found chunk in chunk_list
 * @retval -1: means that the chunk was not found
 */
int32_t allocator_find_chunk(ChunkList chunk_list, void* ptr);

/**
 * @brief Inserts (in a sorting manner) a new chunk into `chunk_list`
 * 
 * @param chunk_list the list to be inserted into
 * @param start the start pointer of the new chunk (sorted by this value)
 * @param size the size of the new chunk
 */
void allocator_insert_chunk(ChunkList* chunk_list, void* start, size_t size);

/**
 * @brief Removes a chunk with the index `index` from `chunk_list`
 * 
 * @param chunk_list the list to remove the chunk from
 * @param index the index of the chunk to be removed
 */
void allocator_remove_chunk(ChunkList* chunk_list, int32_t index);


#endif /* __ALLOCATOR_INTERNAL_H__ */