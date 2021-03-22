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
        hash = ((hash << 5) + hash) + c;
        c = str[++compt];
    }
    return hash;
}