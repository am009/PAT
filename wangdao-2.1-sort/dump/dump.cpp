#include <stdio.h>

int main()
{
    char c;
    c = getchar();
    while(c>=0)
    {
        putchar(c);
        c = getchar();
    }
    
    return 0;
}