#include <cstdio>

using namespace std;

const int DIVISOR = 1000000007;

char str[100005];

int main()
{
    int count[3] = {0};
    scanf("%s", str);

    for (int i = 0; str[i] != '\0'; ++i) {
        
        if ((count[0] == 0 && str[i] != 'P') || 
            (count[1] == 0 && str[i] == 'T')) {
            continue;
        }

        switch(str[i]) {
            case 'P':
                ++count[0];
                break;
            case 'A':
                count[1] += count[0];
                break;
            case 'T':
                count[2] += count[1];
                if (count[2] > DIVISOR) {
                    count[2] %= DIVISOR;
                }
                break;
            default:
                break;
        }
    }

    printf("%d\n", count[2]);

    return 0;
}
