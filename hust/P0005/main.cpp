#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

// define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

using namespace std;

class man {
public:
    int height;
    int wealth;
    int age;
    int handsome;
    int index;
    bool operator <(const man& other) const {
        if (this->handsome != other.handsome) {
            return !(this->handsome > other.handsome);
        }
        if (this->height != other.height) {
            return !(this->height > other.height);
        }
        if (this->wealth != other.wealth) {
            return !(this->wealth > other.wealth);
        }
        if (this->age != other.age) {
            return !(this->age < other.age);
        }
        return !(this->index < other.index);
    }
};

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    #endif
    int count, k;
    // cin >> count >> k;
    scanf("%d%d", &count, &k);
    // printf("nk: %d %d\n", count, k);
    // man * ms = new man[count];
    vector<man> ms(count);

    for(int i=0;i<count;i++) {
        ms[i].index = i+1;
        // cin >> ms[i].height >> ms[i].wealth >> ms[i].handsome >> ms[i].age;
        scanf("%d%d%d%d", &ms[i].height, &ms[i].wealth, &ms[i].handsome, &ms[i].age);
    }
    // sort(ms, ms+count);
    // bubble sort
    // for(int i=0;i<k;i++) {
    //     man max = ms[i];
    //     int max_ind = i;
    //     for(int j=i+1;j<count;j++) {
    //         if (ms[j] < max) {
    //             max = ms[j];
    //             max_ind = j;
    //         }
    //     }
    //     swap(ms[max_ind], ms[i]);
    // }
    make_heap(ms.begin(), ms.end());
    bool init = true;
    for(int i=0;i<k;i++) {
        pop_heap(ms.begin(), ms.end());
        if (init) {
            init = false;
            printf("%d",ms.back().index);
        } else {
            printf(" %d",ms.back().index);
        }
        ms.pop_back();
    }
    return 0;
}