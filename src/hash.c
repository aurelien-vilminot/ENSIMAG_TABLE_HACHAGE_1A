#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../include/hash.h"

uint32_t hash(const char *str)
{
    uint32_t hash = 5381;
    uint32_t compt = 0;

    char c = str[compt];
    while (c != '\0') {
        printf("%c", c);
        hash = ((hash << 5) + hash) + c;
        c = str[++compt];
    }
    return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
    unsigned int hash = 5381;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
}


//int main(void)
//{
//    printf("%u \n", hash("test"));
//    printf("%u \n", DJBHash("test", strlen("test")));
//    printf("%u \n", DJBHash("Caporal Ketchup", strlen("Caporal Ketchup")));
//    printf("%u \n", DJBHash("Colonel Moutarde", strlen("Colonel Moutarde")));
//    printf("%u \n", DJBHash("Sergent Mayo", strlen("Sergent Mayo")));
//    uint64_t test = 193506769;
//    test = test * 33;
//    //printf("%lu\n", test);
//    return EXIT_SUCCESS;
//}