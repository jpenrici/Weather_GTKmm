/* 
 * Reference
 *      curl : command line tool and libraryfor transferring data with URLs
 *      https://curl.se
 * 
 * Requeriment
 *      libcurl4-gnutls-dev
 *      libcurl4-openssl-dev
 *
 */

#ifndef __CURL_CONNECT_H_
#define __CURL_CONNECT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

#ifdef __cplusplus
extern "C" {
#endif
    struct MemoryStruct getData(const char* url);
#ifdef __cplusplus
}
#endif

#endif // __CURL_CONNECT_H_