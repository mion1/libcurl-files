/*
 * =====================================================================================
 *
 *       Filename:  store-in-memory.c
 *
 *    Description:  store data in memory
 *
 *        Version:  1.0
 *        Created:  11/25/2022 05:11:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  JAYANTH J (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#define URL "https://curl.se/"

struct MemoryChunk {
        char *memory_size;
        size_t bytes;
};

size_t static receive_x(char *, size_t, size_t, void *);

int main(void)
{
        curl_global_init(CURL_GLOBAL_ALL);

        CURL *c_handle;
        CURLcode res;
        struct MemoryChunk mem = {
                malloc(1),
                0
        };

        c_handle = curl_easy_init();

        if (c_handle) {
                curl_easy_setopt(c_handle, CURLOPT_URL, URL);
                curl_easy_setopt(c_handle, CURLOPT_WRITEFUNCTION, receive_x);
                curl_easy_setopt(c_handle, CURLOPT_WRITEDATA, &mem);
                res = curl_easy_perform(c_handle);
        }

        if (res != CURLE_OK) {
                fprintf(stderr, "curl didn't return curle_ok\n");
                return 1;
        }

        fprintf(stdout, "%zu\n", mem.bytes);

        curl_easy_cleanup(c_handle);
        curl_global_cleanup();
        free(mem.memory_size);
        return 0;
}

size_t static receive_x(char *buf, size_t size, size_t nmemb, void *potr)
{
        struct MemoryChunk *mem;
        char *ptr;

        mem = (struct MemoryChunk *) potr;
        ptr = realloc(mem->memory_size, nmemb * size + 1);

        if (!ptr) {
                fprintf(stderr, "realloc failed, returned NULL\n");
                return 1;
        }

        mem->memory_size = ptr;
        memcpy(mem->memory_size, buf, nmemb * size + 1);
        mem->bytes += nmemb * size;
        return nmemb * size;
}
