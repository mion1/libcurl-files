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

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#define URL "https://curl.haxx.se/"

struct MemoryChunk {
        char *memory_size;
};

int main(void)
{
        curl_global_init(CURL_GLOBAL_ALL);

        CURL *c_handle;

        c_handle = curl_easy_init();
        if (c_handle) {
                curl_easy_setopt(c_handle, CURLOPT_URL, URL);
        }

        return 0;
}
