#include <stdio.h>
#include <stdlib.h>

#include "leveldata.h"

int main(int argc, char* argv[])
{
    if (argc != 2){
        printf("Expected: main <levelfile>");
        return 0;
    }
    FILE *levelFilePtr = fopen(argv[1], "rb");
    if (!levelFilePtr){
        printf("File failed to open");
        return 0;
    }

    int diff = IsCCLeastAll(levelFilePtr);

    if (diff == 0){
        printf("CC will be all.");
    }
    else{
        printf("CC will be at least, with %d extra objects.", diff);
    }
    return 0;
}