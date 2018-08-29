#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string s;
    getline(cin, s);

    int len = s.length(), longest_sym_len = 1;
    vector<vector<bool>> dp(len, vector<bool>(len, false));

    for (int i = 0; i < len; ++i) {
        dp[i][i] = true;
        if (i > 0 && s[i] == s[i-1]) {
            dp[i-1][i] = true;
            longest_sym_len = 2;
        }
    }

    for (int l = 3; l <= len; ++l) {
        for (int i = 0; i + l - 1 < len; ++i) {
            int j = i + l - 1;
            if (s[i] == s[j] && dp[i+1][j-1]) {
                dp[i][j] = true;
                longest_sym_len = l;
            }
        }
    }

    printf("%d\n", longest_sym_len);

    return 0;
}