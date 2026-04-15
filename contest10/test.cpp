#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    string s1, s2;
    cin >> s1 >> s2;
    
    int m = s1.length(), n = s2.length();
    vector<vector<int>> max_L(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                max_L[i][j] = max_L[i - 1][j - 1] + 1;
            } else {
                max_L[i][j] = max(max_L[i - 1][j], max_L[i][j - 1]);
            }
        }
    }
    
    cout << (max_L[m][n]*100)/(min(m,n));
    
    return 0;
}