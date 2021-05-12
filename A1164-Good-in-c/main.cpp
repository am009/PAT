#include <cstdio>
#include <iostream>
#include <cstring>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

char map[26][7][5];
char word_buf[15];

int my_getc() {
    int buf = getchar();
    if (buf < 0) {
        DEBUG(printf("#ERR1#");)
        exit(0);
    }
    while(buf == '\r' || buf == '\n') {
        buf = getchar();
    }
    return buf;
}

void get_word(char* buf) {
    int ch = my_getc();
    int ind = 0;
    while(isalpha(ch)) {
        buf[ind] = ch;
        ind ++;
        ch = my_getc();
    }
    buf[ind] = '\x00';
}

void print_chr_line(int cind, int lind) {
    if (cind < 0) {
        DEBUG(printf("#err2#");)
    }
    for(int i=0;i<5;i++) {
        putchar(map[cind][lind][i]);
    }
}

void print_word(char* buf) {
    int len = strlen(buf);
    for(int l=0;l<7;l++) {
        for(int i=0;i<len;i++) {
            print_chr_line(buf[i]-'A', l);
            if (i != len-1) { putchar(' '); }
        }
        if (l != 6) { putchar('\n'); }
    }
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int buf;
    for(int i=0;i<26;i++) {
        for(int j=0;j<7;j++) {
            for(int k=0;k<5;k++) {
                map[i][j][k] = my_getc();
            }
        }
    }
    bool init = true;
    for(;;) {
        get_word(word_buf);
        if (init) {
            init = false;
        } else {
            putchar('\n');
            putchar('\n');
        }
        // printf("%s",word_buf);
        print_word(word_buf);
    }
    
    return 0;
}