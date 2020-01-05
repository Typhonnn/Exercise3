#include "Object.h"
#include <stdio.h>



Object* createObject(char* filename)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Failed Opening File %s! Aborting!", filename);
        return NULL;
    }
    //TODO need to continue the function.
    return NULL;
}

