#include <cstdio>
#include <iostream>
#include <cstring>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

char** arr1; // alumni

char** arr2; // attendent

// index in arr1
bool bigger_birth(int current, int oldest) {
    if (oldest == -1) {
        return true;
    }
    // 对比
    // DEBUG(printf("-------");)
    for(int i=0;i<6;i++) {
        // DEBUG(printf("%c vs %c : %d\n", arr1[current][6+i], arr1[oldest][6+i], i);)
        if (arr1[current][6+i] < arr1[oldest][6+i]) {
            // DEBUG(printf("%s -> %s\n", arr1[oldest], arr1[current]);)
            return true;
        } else if (arr1[current][6+i] > arr1[oldest][6+i]) {
            return false;
        }
    }
    return false;
}

// index in arr2
bool bigger_birth_guest(int current, int oldest) {
    if (oldest == -1) {
        return true;
    }
    // 对比
    for(int i=0;i<6;i++) {
        if (arr2[current][6+i] < arr2[oldest][6+i]) {
            return true;
        }
    }
    return false;
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int count1;
    std::cin >> count1;
    arr1 = new char*[count1];
    for(int i=0;i<count1;i++) {
        arr1[i] = new char[20];
        std::cin >> arr1[i];
    }

    int count2;
    std::cin >> count2;
    arr2 = new char*[count2];
    for(int i=0;i<count2;i++) {
        arr2[i] = new char[20];
        std::cin >> arr2[i];
    }

    int attend_count = 0;
    int oldest_alumni = -1;
    int oldest_guest = -1;
    for(int j=0;j<count2;j++) {
        for(int i=0;i<count1;i++) {
            if(!strcmp(arr1[i], arr2[j])) {
                attend_count ++;
                if (bigger_birth(i, oldest_alumni)) {
                    oldest_alumni = i;
                }
            }
        }
        // guest
        if (bigger_birth_guest(j, oldest_guest)) {
            oldest_guest = j;
        }
    }

    printf("%d\n%s\n", attend_count, oldest_alumni != -1 ? arr1[oldest_alumni] : arr2[oldest_guest]);


    return 0;
}