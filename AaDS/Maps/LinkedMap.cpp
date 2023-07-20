#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
 
using namespace std;
 
int k, n, m, x, y, z;
string q, temp_key, temp_x;
 
struct par {
    string key = "", x = "";
    par *next = nullptr;
    par *prev = nullptr;
};
 
par temp;
 
par *root = nullptr;
par *tail = nullptr;
 
int mod = 100019;
long long mod2 = 1000000001;
long long pwr[20];
vector <par*> a[100019];
 
int get_hash(string kek) {
    long long ans = 0;
    for (int i = 0; i < int(kek.size()); ++i) {
        ans += abs(pwr[i] * (kek[i] - 'a' + 1)) % mod2;
        ans %= mod2;
    }
    ans %= mod;
    return int(ans);
}
 
int main()
{
    ifstream file("linkedmap.in");
    ofstream fole("linkedmap.out");
 
    pwr[0] = 31;
    for (int i = 1; i < 20; ++i) {
        pwr[i] = pwr[i - 1] * 31;
        pwr[i] %= mod2;
    }
 
    file >> q >> temp.key;
 
    while (!file.eof()) {
        int hsh = get_hash(temp.key), ind = -1;
 
        for (int i = 0; i < int (a[hsh].size()); ++i) {
            if (a[hsh][i] != nullptr) {
                if (a[hsh][i] -> key == temp.key) {
                    ind = i;
                    break;
                }
            }
        }
 
        if (q == "put") {
            file >> temp.x;
            if (ind != -1) {
                a[hsh][ind] -> x = temp.x;
            } else {
                ind = int(a[hsh].size());
                a[hsh].push_back(new par);
                if (root == nullptr) {
                    root = a[hsh][ind];
                    tail = a[hsh][ind];
                } else {
                    a[hsh][ind] -> prev = tail;
                    tail -> next = a[hsh][ind];
                    tail = a[hsh][ind];
                }
                a[hsh][ind] -> x = temp.x;
                a[hsh][ind] -> key = temp.key;
            }
        } else
        if (q == "get") {
            if (ind != -1) {
                fole << a[hsh][ind] -> x << '\n';
            } else {
                fole << "none\n";
            }
        } else
        if (q == "delete") {
            if (ind != -1) {
                if (a[hsh][ind] != root) {
                    a[hsh][ind] -> prev -> next = a[hsh][ind] -> next;
                } else {
                    root = a[hsh][ind] -> next;
                }
                if (a[hsh][ind] != tail) {
                    a[hsh][ind] -> next -> prev = a[hsh][ind] -> prev;
                } else {
                    tail = a[hsh][ind] -> prev;
                }
                a[hsh][ind] = nullptr;
            }
        } else
        if (q == "prev") {
            if (ind != -1 && a[hsh][ind] -> prev != nullptr) {
                fole << a[hsh][ind] -> prev -> x << '\n';
            } else {
                fole << "none\n";
            }
        } else
        if (q == "next") {
            if (ind != -1 && a[hsh][ind] -> next != nullptr) {
                fole << a[hsh][ind] -> next -> x << '\n';
            } else {
                fole << "none\n";
            }
        }
 
        file >> q >> temp.key;
    }
 
    return 0;
}
