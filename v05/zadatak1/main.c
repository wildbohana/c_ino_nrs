#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BitsBuffer.h"

int main()
{
    bitbuffer b;
    initbuff(&b);

    char message[] = "010010";

    for(int i=0; i < strlen(message); i++){
        push(&b, message[i] - '0');
    }

    while(!isEmpty(b)) {
       int num = pop(&b);
       printf("%d", num);
    }

    return 0;
}
