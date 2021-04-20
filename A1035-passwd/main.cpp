// 简单的字符串处理
#include <cstdio>

// 由于需要先输出被修改的个数，所以得把被修改了的都保存起来。
// 用一个函数修改密码，并且返回bool类型表示是否修改。

bool modify(char* pwd) {
    char* cur = pwd;
    char c = *cur;
    bool mod = false;
    while(c != '\x00') {
        if (c == '1') {
            *cur = '@';
            mod = true;
        }
        if (c == '0') {
            *cur = '%';
            mod = true;
        }
        if (c == 'l') {
            *cur = 'L';
            mod = true;
        }
        if (c == 'O') {
            *cur = 'o';
            mod = true;
        }

        cur++;
        c = *cur;
    }
    return mod;
}

char* moded_tname[1001];
char* moded[1001];
int moded_count = 0;

int account_count = 0;

int main () {
    int count;
    scanf("%d", &count);
    account_count = count;
    moded[moded_count] = new char[11]; moded_tname[moded_count] = new char[11];

    while(count--) {
        scanf("%s%s", moded_tname[moded_count], moded[moded_count]);
        bool ismod = modify(moded[moded_count]);
        if (ismod) {
            moded_count ++; moded[moded_count] = new char[11]; moded_tname[moded_count] = new char[11];
        }
    }

    // ------

    if (moded_count != 0) {
        printf("%d", moded_count);
        for(int i=0;i<moded_count;i++) {
            printf("\n%s %s", moded_tname[i], moded[i]);
        }
    } else {
        if (account_count == 1) {
            printf("There is 1 account and no account is modified");
        } else {
            printf("There are %d accounts and no account is modified", account_count);
        }
    }


    return 0;
}