#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
 
using namespace std;
 
int k, n, m, x, y, z;
string q, temp_key, temp_x;
 
struct par {
    string key, x;
};
 
par temp;
int mod = 100019;
long long mod2 = 1000000001;
long long pwr[20];
vector <par> a[100019];
 
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
    ifstream file("map.in");
    ofstream fole("map.out");
 
    pwr[0] = 31;
    for (int i = 1; i < 20; ++i) {
        pwr[i] = pwr[i - 1] * 31;
        pwr[i] %= mod2;
    }
 
    file >> q >> temp.key;
 
    while (!file.eof()) {
        int hsh = get_hash(temp.key), ind = -1;
 
        for (int i = 0; i < int (a[hsh].size()); ++i) {
            if (a[hsh][i].key == temp.key) {
                ind = i;
                break;
            }
        }
        switch (q[0]) {
        case 'p' : {
            file >> temp.x;
            if (ind != -1) {
                a[hsh][ind].x = temp.x;
            } else {
                a[hsh].push_back(temp);
            }
        } break;
        case 'g' : {
            if (ind != -1) {
                fole << a[hsh][ind].x << '\n';
            } else {
                fole << "none\n";
            }
        } break;
        case 'd' : {
            if (ind != -1) {
                a[hsh][ind].x = "none";
            }
        }
 
        }
        file >> q >> temp.key;
    }
 
    return 0;
}
