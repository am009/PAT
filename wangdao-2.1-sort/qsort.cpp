#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b)
{
    return (*(int*)a)-(*(int*)b);
}

int main ()
{
    int n;scanf("%d\n", &n);
    int *data = (int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++)
    {
        if (i != (n-1))
        {
            scanf("%d ",&data[i]);
        } else {
            scanf("%d",&data[i]);
        }
        
    }
    // todo sort
    qsort(data, n, sizeof(int), cmp);

    for(int i=0;i<n;i++)
    {
        if (i != (n-1))
        {
            printf("%d ", data[i]);
        } else {
            printf("%d\n", data[i]);
        }

    }
}
