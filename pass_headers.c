/*
 * =====================================================================================
 *
 *       Filename:  pass_headers.c
 *
 *    Description:  use curl_append_slist 
 *
 *        Version:  1.0
 *        Created:  11/26/2022 12:03:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  OLIVER J (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main(void)
{
        struct curl_slist *head = NULL;
        struct curl_slist *slist = NULL;
        CURL *c_handle;
        CURLcode res;

        slist = curl_slist_append(head, "accept: */*");
        slist = curl_slist_append(slist, "connection: close");

        curl_global_init(CURL_GLOBAL_ALL);
        c_handle = curl_easy_init();

        if (c_handle) {
                curl_easy_setopt(c_handle, CURLOPT_URL, "https://curl.se");
                curl_easy_setopt(c_handle, CURLOPT_HTTPHEADER, slist);
                res = curl_easy_perform(c_handle);
        }

        if (res != CURLE_OK)
                return -1;

        curl_global_cleanup();
        curl_easy_cleanup(c_handle);
        return 0;
}
