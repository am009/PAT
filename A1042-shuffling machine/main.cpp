#include <cstdio>


int arr1[55] = {0};
int arr2[55] = {0};
int shf[55] = {0};
int* source;
int* dest;

void shuffle(int* shf, int* src, int* dst) {
    for(int i=1;i<55;i++) {
        int ind = shf[i];
        dst[ind] = src[i];
    }
}

void i2s(int i) {
    static const char* s[] = {"S", "H", "C", "D", "J"};
    int ind = i / 13;
    printf("%s", s[ind]);
    printf("%d", (i%13)+1);
}

int main() {
    int times;
    scanf("%d", &times);
    // int i = 54;
    for(int i=1;i<55;i++) {
        scanf("%d", &shf[i]);
        arr1[i] = i;
    }
    source = arr1;
    dest = arr2;
    int *tmp;
    while(times --) {
        shuffle(shf, source, dest);
        tmp = source; source = dest; dest = tmp;
    }
    for(int i=1;i<55;i++) {
        if (i != 54) {
            // printf("%d ", source[i]);
            i2s(source[i]-1);
            printf(" ");
        } else {
            i2s(source[i]-1);
            // printf("%d", source[i]);
        }
    }
}

