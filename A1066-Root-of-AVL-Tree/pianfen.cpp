#include <cstdio>
#include <iostream>
#include <algorithm>

int* datas;

int main () {
    int count;
    std::cin >> count;
    datas = new int[count];
    for(int i=0;i<count;i++) {
        std::cin >> datas[i];
    }
    std::sort(datas, datas + count);
    int mid = count / 2;
    std::cout << datas[mid];
    return 0;
}