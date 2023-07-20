#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
 
using namespace std;
 
int k, n, m, x, y, hsh2;
string q, temp_key, temp_x;
int pwrmod = 31;
int mod1 = 100043, ind2, mod2 = 101;
long long pwr[20];
 
struct par {
    string key = "";
    vector <string> x[101];
    int cnt;
};
 
vector <par*> a[100043];
 
int get_hash(string kek, int mod) {
    long long ans = 0;
    for (int i = 0; i < int(kek.size()); ++i) {
        ans += abs(pwr[i] * (kek[i] - 'a' + 1));
    }
    ans %= mod;
    return int(abs(ans));
}
 
int main()
{
    ifstream file("multimap.in");
    ofstream fole("multimap.out");
 
    ios_base::sync_with_stdio(0);
    pwr[0] = pwrmod;
    for (int i = 1; i < 20; ++i) {
        pwr[i] = abs(pwr[i - 1] * pwrmod);
        pwr[i] %= 100000000001;
    }
 
    file >> q >> temp_key;
 
    while (!file.eof()) {
        int hsh = get_hash(temp_key, mod1), ind = -1;
 
        for (int i = 0; i < int (a[hsh].size()); ++i) {
            if (a[hsh][i] != nullptr) {
                if (a[hsh][i] -> key == temp_key) {
                    ind = i;
                    break;
                }
            }
        }
 
        if (q == "put") {
            file >> temp_x;
            hsh2 = get_hash(temp_x, mod2);
            if (ind != -1) {
                ind2 = -1;
                for (int j = 0; j < int(a[hsh][ind] -> x[hsh2].size()); ++j) {
                    if (a[hsh][ind] -> x[hsh2][j] == temp_x) {
                        ind2 = j;
                        break;
                    }
                }
                if (ind2 == -1) {
                    ++a[hsh][ind] -> cnt;
                    a[hsh][ind] -> x[hsh2].push_back(temp_x);
                }
            } else {
                ind = int(a[hsh].size());
                a[hsh].push_back(new par);
                a[hsh][ind] -> cnt = 1;
                a[hsh][ind] -> x[hsh2].push_back(temp_x);
                a[hsh][ind] -> key = temp_key;
            }
        } else
        if (q == "get") {
            if (ind != -1) {
                fole << a[hsh][ind] -> cnt << ' ';
                for (int j = 0; j < mod2; ++j) {
                    for (int z = 0; z < int(a[hsh][ind] -> x[j].size()); ++z) {
                        fole << a[hsh][ind] -> x[j][z] << ' ';
                    }
                }
                fole << '\n';
            } else {
                fole << "0\n";
            }
        } else
        if (q == "delete") {
            file >> temp_x;
            hsh2 = get_hash(temp_x, mod2);
            if (ind != -1) {
                ind2 = -1;
                for (int j = 0; j < int(a[hsh][ind] -> x[hsh2].size()); ++j) {
                    if (a[hsh][ind] -> x[hsh2][j] == temp_x) {
                        ind2 = j;
                        break;
                    }
                }
                if (ind2 != -1) {
                    swap(a[hsh][ind] -> x[hsh2][ind2], a[hsh][ind] -> x[hsh2].back());
                    a[hsh][ind] -> x[hsh2].pop_back();
                    --a[hsh][ind] -> cnt;
                }
            }
        } else
        if (q == "deleteall") {
            if (ind != -1) {
                a[hsh][ind] = nullptr;
            }
        }
 
        file >> q >> temp_key;
    }
 
    return 0;
}
