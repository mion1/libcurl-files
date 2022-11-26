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
#include <stdlib.h>
#include <curl/curl.h>

#define C_URL "https://www.theanneboleynfiles.com"

size_t static receive_x(char *, size_t, size_t, void *);

struct data_struct {
        char *filename;
        FILE *file;
};

int main(void)
{
        curl_global_init(CURL_GLOBAL_ALL);
        struct curl_slist *cookie_jar = NULL;
        CURL *curl;
        CURLcode res;
        struct data_struct info = {
                "rooster.txt",
                NULL,
        };

        curl = curl_easy_init();
        
        if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, C_URL);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, receive_x);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &info);
                curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
                res = curl_easy_perform(curl);
        }

        if (res != CURLE_OK) {
                fprintf(stderr, "curl failed: %s\n", curl_easy_strerror(res));
                return -1;
        }

        res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookie_jar);

        if (res != CURLE_OK) {
                fprintf(stderr, "couldn't fetch cookies: %s\n", \
                                curl_easy_strerror(res));
                return -1;
        }

        struct curl_slist *hld = cookie_jar;

        while (hld) {
                printf(" %s\n", hld->data);
                hld = hld->next;
                if (!hld)
                        break;
        }

        fclose(info.file);
        curl_slist_free_all(cookie_jar);
        curl_slist_free_all(hld);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 0;
}

size_t static receive_x(char *buf, size_t size, size_t nmemb, void *ptr)
{
        struct data_struct *temp = (struct data_struct *) ptr;
        temp->file = fopen(temp->filename, "a+");
        if (!temp->file) {
                fprintf(stderr, "file could not be opened\n");
                return -1;
        }
        return fwrite(buf, size, nmemb, temp->file);
}
