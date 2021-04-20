// 打印一个U形的字符
// 设三条边分别是n1 n2 n3，其中n1=n3，n1需要小于n2，并且尽可能大。

#include <cstdio>
#include <cstring>

char orig[81];

int main () {
    int len = scanf("%s", orig);
    len = strlen(orig);
    
    int n1 = (len+2) / 3;
    int n2 = (len+2) - n1 - n1;
    // printf("%d %d", n1, n2);

    int width = n2 - 1;

    char* front = orig;
    char* end = &orig[len-1];
    for(int i=0;i<n1-1;i++) {
        printf("%c%*c\n",*front, width, *end);
        front ++;
        end --;
    }
    printf("%.*s", width+1, front);


}
