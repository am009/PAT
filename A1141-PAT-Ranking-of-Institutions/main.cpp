#include <cstdio>
#include <iostream>
#include <map>
#include <cstring>
#include <cctype>
#include <string>
#include <algorithm>
#include <cmath>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

struct school {
    char name[10];
    double tws;
    int ns; // num of student
};
typedef struct school school;

school* data;

std::map<std::string, int> dmap;
int dind = 0;

void to_lower(char* str) {
    while(*str != '\x00') {
        (*str) = tolower(*str);
        str++;
    }
}

double get_score(char* id, int score) {
    if(id[0] == 'A') {
        return score;
    } else if (id[0] == 'B') {
        return score/1.5;
    } else if(id[0] == 'T') {
        return score*1.5;
    } else {
        DEBUG(printf("#err1:%s#", id);)
    }
}

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int count;
    std::cin >> count;
    data = new school[count];
    for(int i=0;i<count;i++) {
        char id[10];
        int score;
        char school[10];
        // get school struct
        std::cin >> id >> score >> school;
        to_lower(school);
        std::string sch(school);
        auto it = dmap.find(sch);
        int ind;
        if (it != dmap.end()) {
            ind = (*it).second;
        } else {
            ind = dind; dind++;
            dmap.insert(std::pair<std::string, int>(sch, ind));
            // init struct
            data[ind].ns = 0;
            data[ind].tws = 0.0;
            strcpy(data[ind].name, school);
        }
        data[ind].ns ++;
        data[ind].tws += get_score(id, score);
    }

    // sort
    std::sort(data, data+dind, [](school &a, school &b) {
        if (a.tws != b.tws) {
            return a.tws > b.tws;
        } else if (a.ns != b.ns) {
            return a.ns < b.ns;
        } else {
            return strcmp(a.name, b.name) < 0;
        }
    });

    printf("%d\n",dind);
    int rank = 1;
    for(int i=0;i<dind;) {
        int current_rank = rank;
        printf("%d %s %.0f %d\n", current_rank, data[i].name, floor(data[i].tws), data[i].ns);
        rank++;
        int tws = floor(data[i].tws);
        i++;
        for(int j=i;j<dind;j++) {
            if(((int)floor(data[j].tws)) != tws) {
                break;
            }
            DEBUG(printf("T");)
            printf("%d %s %.0f %d\n", current_rank, data[j].name, floor(data[j].tws), data[j].ns);
            rank++;
            i++;
        }

    }

    return 0;
}