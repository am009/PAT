#include <cstdio>
#include <algorithm>


int main () {
    int count;
    long long int *dists = new long long int[count*16+16];
    scanf("%d", &count);
    for(int i=0;i<count;i++){
        printf("%d", i);
        scanf("%lld", &dists[i]);
        printf("#");
    }
    return 0;
}
