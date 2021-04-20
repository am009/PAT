#include <cstdio>
#include <algorithm>



int main () {
    int count;
    int sum = 0;
    scanf("%d", &count);
    int *dists = new int[count+1];
    dists[0] = 0;
    for(int i=1;i<=count;i++){
        scanf("%d", &(dists[i]));
        sum += dists[i];
        dists[i] = sum;
    }
    // ----------
    scanf("%d", &count);
    int node1 = 0;
    int node2 = 0;
    int result;
    while(count --) {
        result = 0;
        scanf("%d", &node1);
        scanf("%d", &node2);
        int big = std::max<int>(node1, node2) - 1;
        int small = std::min<int>(node1, node2) - 1;
        result = dists[big] - dists[small];
        result = std::min<int>(result, sum-result);
        printf("%d", result);
        printf("\n");
    }
}
