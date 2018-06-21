#include <cstdio>
#include <unordered_set>

using namespace std;

int main()
{
    char str[2][86];
    scanf("%s %s", str[1], str[0]);

    unordered_set<char> chars;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; str[i][j] != '\0'; ++j) {

            if (str[i][j] >= 'a' && str[i][j] <= 'z') {
                str[i][j] += 'A' - 'a';
            }

            if (i == 1 && chars.find(str[i][j]) == chars.cend()) {
                printf("%c", str[i][j]);
            }

            chars.insert(str[i][j]);
        }
    }

    printf("\n");

    return 0;
}
