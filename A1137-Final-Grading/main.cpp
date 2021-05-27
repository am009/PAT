#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cstring>
#include <cmath>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

struct stu {
    char name[21];
    int assign;
    int mid;
    int final_score;
    int grade;
};

typedef struct stu stu;

int P,M,N;

stu* data;
int dataind = 0;
std::map<std::string, int> indmap;
char buf[22];

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif

    std::cin >> P >> M >> N;
    data = new stu[P+M+N];

    for(int i=0;i<P;i++) {
        int score;
        std::cin >> buf >> score;
        std::string s(buf);
        auto it = indmap.find(s);
        int ind;
        if (it == indmap.end()) {
            ind = dataind;
            indmap.insert(std::pair<std::string, int>(s,ind));
            dataind ++;
            data[ind].assign = -1;
            data[ind].mid = -1;
            data[ind].final_score = -1;
            data[ind].grade = -1;
            strcpy(data[ind].name, buf);
        } else {
            ind = (*it).second;
        }
        DEBUG(std::cout << ind << ": " << s << " assign: " << score  << std::endl;)
        data[ind].assign = score;
        if (score < 200) {
            data[ind].grade = 0;
        }
    }

    for(int i=0;i<M;i++) {
        int score;
        std::cin >> buf >> score;
        std::string s(buf);
        auto it = indmap.find(s);
        int ind;
        if (it == indmap.end()) {
            ind = dataind;
            indmap.insert(std::pair<std::string, int>(s,dataind));
            dataind ++;
            data[ind].assign = -1;
            data[ind].mid = -1;
            data[ind].final_score = -1;
            data[ind].grade = -1;
            strcpy(data[ind].name, buf);
        } else {
            ind = (*it).second;
        }
        DEBUG(std::cout << ind << ": " << s << " mid: " << score  << std::endl;)
        data[ind].mid = score;
    }

    for(int i=0;i<N;i++) {
        int score;
        std::cin >> buf >> score;
        std::string s(buf);
        auto it = indmap.find(s);
        int ind;
        if (it == indmap.end()) {
            ind = dataind;
            indmap.insert(std::pair<std::string, int>(s,dataind));
            dataind ++;
            data[ind].assign = -1;
            data[ind].mid = -1;
            data[ind].final_score = -1;
            data[ind].grade = -1;
            strcpy(data[ind].name, buf);
        } else {
            ind = (*it).second;
        }
        DEBUG(std::cout << ind << ": " << s << " final: " << score << std::endl;)
        data[ind].final_score = score;
        // calc grade
        stu* current = &data[ind];
        if (current->assign >= 200) {
            if (current->mid > current->final_score) {
                current->grade = round(current->final_score * 0.6f + current->mid * 0.4);
            } else {
                current->grade = current->final_score;
            }
        }
    }

    std::sort(data, data+dataind, [](stu a, stu b) {
        if (a.grade != b.grade) {
            return a.grade > b.grade;
        } else {
            return strcmp(a.name, b.name) < 0;
        }
    });

    DEBUG(std::cout << "--------" << std::endl;)
    for(int i=0;i<dataind;i++) {
        if(data[i].grade <60) {
            break;
        }
        printf("%s %d %d %d %d\n", data[i].name, data[i].assign, data[i].mid, data[i].final_score, data[i].grade);
    }
    

    return 0;
}