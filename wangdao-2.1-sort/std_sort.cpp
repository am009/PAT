#include <stdio.h>
#include <functional>
#include <algorithm>

int main()
{
    int n;scanf("%d", &n);
    int* data = new int[n]();
    for(int i=0;i<n;i++)
    {
        scanf("%d", &data[i]);
    }

    std::sort(data, &data[n]);

    for(int i=0;i<n;i++)
    {
        if (i != (n-1))
        {
            printf("%d ", data[i]);
        } else {
            printf("%d\n", data[i]);
        }
    }
    delete[] data;
    return 0;
}