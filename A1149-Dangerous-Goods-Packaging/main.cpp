#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

void overflow() {
    while(1) {puts("wtf");}
}

std::map<std::string, std::set<std::string>> inc_map;

// void my_insert(std::string node1, std::string node2) {
//     std::set<std::string> inc1;
//     std::set<std::string> inc2;
//     inc1.insert(node2);
//     inc2.insert(node1);
//     auto it1 = inc_map.find(node1);
//     if (it1 == inc_map.end()) {
//         inc_map.insert(std::pair<std::string, std::set<std::string>>(node1, inc1));
//     } else {
//         (*it1).second.insert(node2);
//     }
//     auto it2 = inc_map.find(node2);
//     if (it2 == inc_map.end()) {
//         inc_map.insert(std::pair<std::string, std::set<std::string>>(node2, inc2));
//     } else {
//         (*it2).second.insert(node1);
//     }
// }

// std::set<std::string>* my_get(std::string node1) {
//     auto it = inc_map.find(node1);
//     if (it == inc_map.end()) {
//         return nullptr;
//     } else {
//         return &(*it).second;
//     }
// }

int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    int inc_count, list_count;
    std::cin >> inc_count >> list_count;
    for(int i=0;i<inc_count;i++) {
        std::string node1, node2;
        std::cin >> node1 >> node2;
        // my_insert(node1, node2);
        inc_map[node1].insert(node2);
        inc_map[node2].insert(node1);
    }
    for(int i=0;i<list_count;i++) {
        int count; std::cin >> count;
        std::set<std::string> banned;
        // DEBUG(printf("#setlen: %d#\n", banned.size());)
        bool pass = true;
        for(int j=0;j<count;j++) {
            std::string node; std::cin >> node;
            // not 
            // 把node的inc加入banned
            std::set<std::string>& inc = inc_map[node];
            for(auto it = (inc).begin();it != (inc).end(); ++it ) {
                banned.insert(*it);
            }
            if (banned.find(node) != banned.end()) {
                pass = false;
                // break;
            }
        }
        if (pass) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}