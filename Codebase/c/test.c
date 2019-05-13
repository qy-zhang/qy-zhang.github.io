#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int i;
    printf("input num\n");
    scanf("%d", &i);
    i *= 2;
    printf("%d\n", i);

    system("pause");
    return 0;
}
