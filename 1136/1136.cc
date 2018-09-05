#include <iostream>
#include <string>

using namespace std;

string CalculateSum(string &a, const string &b)
{
    int carry = 0;

    for (int i = a.length() - 1; i >= 0; --i) {
        a[i] = a[i] + b[i] + carry - '0';
        carry = 0;
        if (a[i] > '9') {
            a[i] -= 10;
            carry = 1;
        }
    }

    return carry > 0 ? "1" + a : a;
}

int main()
{
    string a;
    cin >> a;

    int times = 0;
    for (string b; times < 10; ++times) {
        b = string(a.rbegin(), a.rend());
        if (a == b) {break;}

        cout << a << " + " << b << " = ";
        a = CalculateSum(a, b);
        cout << a << endl;
    }

    if (times < 10) {
        cout << a << " is a palindromic number." << endl;
    } else {
        cout << "Not found in 10 iterations." << endl;
    }

    return 0;
}