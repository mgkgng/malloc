#include "malloc.h"
#include <string.h>

int main() {
    char *ptr = malloc(256);

    strcpy(ptr + 24, "AGASATANAHAMAYARAWA");
    strcpy(ptr + 72, "non rien de rien, non je ne regrette rien");
    show_alloc_mem_ex(ptr, HEX);
    show_alloc_mem_ex(ptr, ASCII);
}