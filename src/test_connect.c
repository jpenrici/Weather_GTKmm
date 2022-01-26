/* 
 * Reference
 *      curl : command line tool and libraryfor transferring data with URLs
 *      https://curl.se
 * 
 * Requeriment
 *      libcurl4-gnutls-dev
 *
 */

#include "connect.h"

int main(void)
{
    struct MemoryStruct data;
    data = getData("https://www.example.com/");

    printf("%s\n", data.memory);
    printf("%lu bytes retrieved\n", (unsigned long)data.size);

    return 0;
}