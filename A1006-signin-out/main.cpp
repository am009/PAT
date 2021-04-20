//简单的求最值

#include <cstdio>

struct time
{
    char ID[20];
    int hour;
    int min;
    int sec;

    int full_sec() {
        return this->hour * 3600 + this->min * 60 + this->sec;
    }

    bool operator < (struct time & t) {
        return (t.full_sec() - this->full_sec()) > 0;
    }
};



int main () {
    int count;
    scanf("%d", &count);
    struct time maxi, mini;
    struct time tmp;
    bool init = true;
    while(count--) {
        scanf("%s %d:%d:%d", tmp.ID, &tmp.hour, &tmp.min, &tmp.sec);
        // sign in - min
        if (init) {
            mini = tmp;
        } else {
            if (tmp < mini) {
                mini = tmp;
            }
        }
        scanf("%d:%d:%d", &tmp.hour, &tmp.min, &tmp.sec);
        // sign out - max
        if (init) {
            maxi = tmp;
            init = false;
        } else {
            if (maxi < tmp) {
                maxi = tmp;
            }
        }
    }

    printf("%s %s", mini.ID, maxi.ID);

    return 0;
}