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

#include "connect.h"

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(!ptr) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
 
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
 
    return realsize;
}

struct MemoryStruct getData(const char* url)
{
    struct MemoryStruct data;
    data.memory = malloc(1); 
    data.size = 0;

    if (url == NULL || url[0] == '\0') {
        printf("nothing to do\n");
        return data;
    }

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 5000L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 2 );
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&data);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "CurlConnect/1.0");    
 
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();
  }

  printf("%lu bytes loaded\n", (unsigned long)data.size);

  return data;
}
