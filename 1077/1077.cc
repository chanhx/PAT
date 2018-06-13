#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    cin.ignore();

    string kuchiguse;

    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        reverse(line.begin(), line.end());

        if (i == 0) {
            kuchiguse = line;
            continue;
        }

        int j;
        auto min_len = min(line.length(), kuchiguse.length());
        for (j = 0; j < min_len; ++j) {
            if (line[j] != kuchiguse[j]) {break;}
        }
        kuchiguse = kuchiguse.substr(0, j);
        
        if (j == 0) {break;}
    }

    if (kuchiguse.length() > 0) {
        reverse(kuchiguse.begin(), kuchiguse.end());
    } else {
        kuchiguse = "nai";
    }

    cout << kuchiguse << endl;

    return 0;
}
