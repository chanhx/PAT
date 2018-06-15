#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    string number[] = {
        "ling", "yi", "er", "san", "si",
        "wu", "liu", "qi", "ba", "jiu"
    };
    map<int, const string> wei = {{9, "Yi"}, {5, "Wan"}, {4, "Qian"}, {3, "Bai"}, {2, "Shi"}};

    string str;
    cin >> str;

    int i = 0;

    if (str[i] == '-') {
        cout << "Fu";
        ++i;
    }

    auto end = str.length() - 1, send = end;

    while (i + 4 <= send) {
        send -= 4;
    }

    int zeros = 0;
    for (; i <= end; ++i) {
        
        if (str[i] == '0') {
            ++zeros;
        } else {
            if (i != 0) {cout << ' ';}

            if (zeros > 0) {
                cout << number[0] << ' ';
                zeros = 0;
            }
            
            cout << number[str[i]-'0'];

            if (wei.find(send-i+1) != wei.cend()) {
                cout << ' ' << wei[send-i+1];
            }
        }

        if (i != send) {continue;}

        if (zeros < 4 && wei.find(end-send+1) != wei.cend()) {
            cout << ' ' << wei[end-send+1];
        }
        send += 4;
    }

    if (zeros == str.length()) {
        cout << number[0];
    }
    cout << endl;

    return 0;
}
