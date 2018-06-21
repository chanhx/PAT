#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

int main()
{
    map<char, int> beads;

    char s[1001];
    scanf("%s", s);

    int missing_beads_count = 0,
        extra_beads_count = strlen(s);

    for (int i = 0; s[i] != '\0'; ++i) {
        if (beads.find(s[i]) == beads.cend()) {
            beads[s[i]] = 0;
        }

        ++beads[s[i]];
    }

    scanf("%s", s);

    for (int i = 0; s[i] != '\0'; ++i) {
        if (beads.find(s[i]) != beads.cend() && beads[s[i]] > 0) {
            --beads[s[i]];
            --extra_beads_count;
        } else {
            ++missing_beads_count;
        }
    }

    if (missing_beads_count > 0) {
        printf("No %d\n", missing_beads_count);
    } else {
        printf("Yes %d\n", extra_beads_count);
    }

    return 0;
}
