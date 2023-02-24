#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "script.h"



int main(void)
{

    char Image[40];

    printf("Donner le nom de l'image : ");
    fgets(Image,40,stdin);

    CreateFile(Image);

    read_line("Tempfile.txt");
    remove("Tempfile.txt");
    remove("Ntest.jpg");

    return 0;


}
