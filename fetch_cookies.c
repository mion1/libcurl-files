/*
 * =====================================================================================
 *
 *       Filename:  fetch_cookies.c
 *
 *    Description:  netscape format cookies 
 *
 *        Version:  1.0
 *        Created:  11/26/2022 02:13:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  OLIVER J (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <curl/curl.h>

#define C_URL "https://curl.se"

int main(void)
{
        curl_global_init(CURL_GLOBAL_ALL);
        struct curl_slist *cookie_jar = NULL;
        CURL *curl;
        CURLcode res;

        curl_easy_init(curl);
        
        if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, C_URL);
                curl_easy_setopt(curl, CURLINFO_COOKIELIST, &cookie_jar);
                res = curl_easy_perform(curl);
        }

        if (res != CURLE_OK) {
                fprintf(stderr, "curl failed: %s\n", curl_easy_strerror(res));
                return -1;
        }

        curl_easy_cleanup(curl);
        curl_global_cleanup();
}
