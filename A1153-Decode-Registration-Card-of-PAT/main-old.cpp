#include <cstdio>
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <set>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

struct total {
    int people;
    int score;
};
typedef struct total total;

std::map<std::string, total> site2total;

// site use string
// date->site->numofpeople
std::map<std::string, std::unordered_map<std::string, int>> date2t3;

typedef std::pair<std::string, int> stu;

struct compare {
    bool operator () (std::pair<std::string, int> &a, std::pair<std::string, int> &b){
        if(a.second != b.second) {
            return a.second > b.second;
        } else {
            return a.first < b.first;
        }
    }
};

bool cmp (std::pair<std::string, int> &a, std::pair<std::string, int> &b) {
        if(a.second != b.second) {
            return a.second > b.second;
        } else {
            return a.first < b.first;
        }
}

std::set<stu, compare> top;
std::set<stu, compare> adv;
std::set<stu, compare> bas;
std::vector<stu> all;


std::set<stu, compare>* char2vec(char c) {
    std::set<stu, compare>* vec;
    switch (c)
    {
    case 'B':
        vec=&bas;
        break;
    case 'A':
        vec=&adv;
        break;
    case 'T':
        vec=&top;
        break;
    default:
        DEBUG(printf("#err1#"); return nullptr;)
        break;
    }
    return vec;
}

bool in_site(std::string id, std::string site)  {
    return strncmp(id.c_str()+1, site.c_str(), 3) == 0;
    // return id.substr(1,3) == site;
}

bool in_date(std::string id, std::string date)  {
    return strncmp(id.c_str()+4, date.c_str(), 6) == 0;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int stu_count, que_count;
    std::cin >> stu_count >> que_count;
    std::vector<stu> all_stu(stu_count);
    for(int i=0;i<stu_count;i++) {
        std::cin >> all_stu[i].first >> all_stu[i].second;
        std::string &id = all_stu[i].first;
        auto vec_p = char2vec(id.c_str()[0]);
        (*vec_p).insert(all_stu[i]);
    }
    for(int i=1;i<=que_count;i++) {
        std::string query;
        int ty; std::cin >> ty >> query;
        printf("Case %d: %d %s\n", i, ty, query.c_str());
        std::vector<stu> ans;
        if(ty == 1) {
            // for(int j=0;j<stu_count;j++) {
            //     if (all_stu[j].first[0] == query[0]) {
            //         ans.push_back(all_stu[j]);
            //     }
            // }
            // sort(ans.begin(), ans.end(), compare());
            // for (int j = 0; j < ans.size(); j++) {
            //     printf("%s %d\n", ans[j].first.c_str(), ans[j].second);
            // }
            // if (ans.size() == 0) {
            //     printf("NA\n");
            // }
            // ------------
            std::set<stu, compare>* vec = char2vec(query[0]);
            for(auto &ele : (*vec)) {
                // std::cout <<  << " " << ele.second << std::endl;
                printf("%s %d\n", ele.first.c_str(), ele.second);
            }
            if((*vec).size() == 0) {
                printf("NA\n");
            }
            continue;
        } else if (ty == 2) {
            // 通过考场打印出总人数和总分数
            // int cnt = 0, sum = 0;
            // for(int j=0;j<stu_count;j++) {
            //     if (all_stu[j].first.substr(1,3) == query) {
            //         cnt++;
            //         sum += all_stu[j].second;
            //     }
            // }
            // if (cnt == 0) {
            //     printf("NA\n");
            // } else {
            //     printf("%d %d\n", cnt, sum);
            // }
            // ----------------------
            int num_people = 0, total_score = 0;
            for (auto &stu : all_stu) {
                // if (all_stu[j].first.substr(1,3) == query) {
                if (in_site(stu.first, query)) {
                    // DEBUG(printf("%s %s\n", all_stu[j].first.c_str(), query.c_str());)
                    num_people ++; total_score += stu.second;
                }
            }
            if (num_people == 0) {
                printf("NA\n");
            } else {
                printf("%d %d\n", num_people, total_score);
            }
            continue;
        } else if (ty == 3) {
            std::unordered_map<std::string, int> m;
            for(int j=0;j<stu_count;j++) {
                if(all_stu[j].first.substr(4,6) == query) {
                    m[all_stu[j].first.substr(1,3)]++;
                }
            }
            for(auto &item: m) {
                ans.push_back({item.first, item.second});
            }
            sort(ans.begin(), ans.end(), compare());
            for (int j = 0; j < ans.size(); j++) {
                printf("%s %d\n", ans[j].first.c_str(), ans[j].second);
            }
            if ((ty == 3) && ans.size() == 0) {
                printf("NA\n");
            }

        } else {
            DEBUG(printf("#err2:%d#", ty);)
        }
            
    }
}

int main1 () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int stu_count, que_count;
    std::cin >> stu_count >> que_count;
    std::vector<stu> all_stu(stu_count);
    for(int i=0;i<stu_count;i++) {
        std::cin >> all_stu[i].first >> all_stu[i].second;
        std::string &id = all_stu[i].first;
        auto vec_p = char2vec(id.c_str()[0]);
        (*vec_p).insert(all_stu[i]);
    }

    for(int i=1;i<=que_count;i++) {
        int ty; std::cin >> ty;
        if(ty == 1) {
            std::string level;
            std::cin >> level;
            char c = level.c_str()[0];
            std::set<stu, compare>* vec = char2vec(c);
            // std::cout << "Case " << i << ": " << ty << " " << c << std::endl;
            printf("Case %d: %d %s\n", i, ty, level.c_str());
            for(auto &ele : (*vec)) {
                std::cout << ele.first << " " << ele.second << std::endl;
            }
        } else if (ty == 2) {
            // 通过考场打印出总人数和总分数
            std::string site;
            std::cin >> site;
            // std::cout << "Case " << i << ": " << ty << " " << site << std::endl;
            printf("Case %d: %d %s\n", i, ty, site.c_str());
            int num_people = 0, total_score = 0;
            for (auto &stu : all_stu) {
                if (in_site(stu.first, site)) {
                    DEBUG(printf("%s %s\n", stu.first.c_str(), site.c_str());)
                    num_people ++; total_score += stu.second;
                }
            }
            if (num_people == 0) {
                std::cout << "NA" << std::endl;
                continue;
            } else {
                std::cout << num_people << " " << total_score << std::endl;
            }
        } else if (ty == 3) {
            std::string date;
            std::cin >> date;
            std::unordered_map<std::string, int> site2num;
            // std::cout << "Case " << i << ": " << ty << " " << date << std::endl;
            printf("Case %d: %d %s\n", i, ty, date.c_str());
            bool na = true;
            for (auto &stu : all_stu) {
                if (in_date(stu.first, date)) {
                    site2num[stu.first.substr(1, 3)] ++;
                    na = false;
                }
            }
            if (na) {
                std::cout << "NA" << std::endl;
                continue;
            } else {
                std::set<std::pair<std::string, int>, compare> site_set;
                for(auto &ele: site2num) {
                    site_set.insert(ele);
                }
                for(auto &ele: site_set) {
                    std::cout << ele.first << " " << ele.second <<  std::endl;
                }
            }
        } else {
            DEBUG(printf("#err2:%d#", ty);)
        }
    }
    return 0;
}