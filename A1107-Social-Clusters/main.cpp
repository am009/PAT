#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>


// 爱好到人的编号。
std::map<int, std::vector<int>> hob_per;
typedef std::map<int, std::vector<int>>::iterator mapit;
typedef std::vector<int>::iterator vecit;

int *person_sets;
int COUNT;
int* grp_nums;

int find(int ind) {
    int orig = ind;
    while(person_sets[ind] != ind) {
        ind = person_sets[ind];
    }
    while (orig != ind) {
        int next = person_sets[orig];
        person_sets[orig] = ind;
        orig = next;
    }
    return ind;
}

void merge(int ind1, int ind2) {
    int f1 = find(ind1);
    int f2 = find(ind2);
    if(f1 != f2) {
        person_sets[f1] = f2;
    }
}

int main () {
    std::cin >> COUNT;
    grp_nums = new int[COUNT];
    person_sets = new int[COUNT];
    for(int i=0;i<COUNT;i++) {
        person_sets[i] = i;
        grp_nums[i] = 0;
    }
    for(int i=0;i<COUNT;i++) {
        int count;
        scanf("%d:", &count);
        for(int j=0;j<count;j++) {
            int hob;
            std::cin >> hob;
            mapit it = hob_per.find(hob);
            if (it != hob_per.end()) { // 有
                // 遍历并合并。
                vecit vit;
                std::vector<int> & vec = (*it).second;
                for(vit=vec.begin();vit!=vec.end();vit++) {
                    // （*vit）和i合并 TODO
                    merge((*vit), i);
                }
                (*it).second.push_back(i);
            } else { // 没有
                std::vector<int> vec = {i};
                hob_per.emplace(hob, vec);
            }
        }
    }

    // 遍历查
    for(int i=0;i<COUNT;i++) {
        grp_nums[find(i)] ++;
    }
    std::sort(grp_nums, grp_nums+COUNT, std::greater<int>());
    
    int num = 0;
    for(int i=0;grp_nums[i] != 0;i++) {
        num ++;
    }
    printf("%d\n", num);
    bool init = true;
    for(int i=0;grp_nums[i] != 0;i++) {
        if (init) {
            init = false;
            printf("%d", grp_nums[i]);
        } else {
            printf(" %d", grp_nums[i]);
        }
    }


    return 0;
}