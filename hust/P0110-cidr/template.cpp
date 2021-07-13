#include <cstdio>
#include <iostream>
#include <string>
#include <cstdint>
#include <set>
#include <algorithm>
#include <sstream>

#ifndef ONLINE_JUDGE
#define DEBUG(X) X
#else
#define DEBUG(X) 
#endif

using namespace std;

class ipaddr {
public:
    uint8_t addr[4];
    int mask;
    bool operator <(const ipaddr& other) const {
        for(int i=0;i<4;i++) {
            if (this->addr[i] != other.addr[i]) {
                return this->addr[i] < other.addr[i];
            }
        }
        return this->mask < other.mask;
    }
    bool operator ==(ipaddr& other) {
        for(int i=0;i<4;i++) {
            if (this->addr[i] != other.addr[i]) {
                return false;
            }
        }
        return this->mask == other.mask;
    }
    void print() const {
        printf("%d.%d.%d.%d/%d\n",addr[0], addr[1], addr[2], addr[3], mask);
    }
};

using namespace std;

uint8_t mask_arr[] = {0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};


int main () {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    #endif

    set<ipaddr> ipset;
    
    while(!cin.eof()) {
        string line;
        getline(cin, line, '\n');
        size_t pos = line.find("/");
        string p1 = line, p2 = "";
        if (pos != string::npos) {
            p1 = line.substr(0, pos);
            p2 = line.substr(pos+1);
        }
        size_t dot_count = count(p1.begin(), p1.end(), '.');
        int mask = (dot_count + 1) * 8;
        if (!p2.empty()) {
            mask = stol(p2);
        }
        ipaddr tmp = {0};
        int tmask = mask;
        int ind = 0;
        int scan_pos = 0;
        // 1/16
        while(tmask > 0) {
            // scan a int
            int new_pos = p1.find('.', scan_pos);
            if (new_pos == string::npos) {new_pos = p1.length();}
            int out;
            if (new_pos - scan_pos > 0) {
                out = stoi(p1.substr(scan_pos, new_pos - scan_pos));
                scan_pos = new_pos + 1;
            } else {
                out = 0;
            }
            

            if (tmask >= 8) {
                tmp.addr[ind] = out;
            } else {
                tmp.addr[ind] = out & mask_arr[tmask];
            }

            tmask -= 8;
            ind ++;
        }
        tmp.mask = mask;

        ipset.insert(tmp);
    }

    
    for(const ipaddr& ele: ipset) {
        ele.print();
    }


    return 0;
}