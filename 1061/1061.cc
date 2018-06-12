#include <cstdio>
#include <cctype>
#include <cstring>

const char * WEEKDAYS[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

int main()
{
    char str1[70], str2[70], str3[70], str4[70];
    scanf("%s %s %s %s", str1, str2, str3, str4);

    const char *day;
    int hour, minute = 0;

    auto len1 = strlen(str1), len2 = strlen(str2), 
         len3 = strlen(str3), len4 = strlen(str4);
    int i;

    for (i = 0; i < len1 && i < len2; ++i) {

        if (str1[i] != str2[i]) {continue;}
        if (str1[i] < 'A' || str1[i] > 'G') {continue;}

        day = WEEKDAYS[str1[i] - 'A'];
        break;
    }

    for (++i; i < len1 && i < len2; ++i) {

        if (str1[i] != str2[i]) {continue;}

        if (str1[i] >= 'A' && str1[i] <= 'N') {
            hour = str1[i] - 'A' + 10;
            break;
        } else if (std::isdigit(str1[i])) {
            hour = str1[i] - '0';
            break;
        }
    }

    for (i = 0; i < len3 && i < len4; ++i) {

        if (str3[i] == str4[i] && std::isalpha(str3[i])) {
            minute = i;
            break;
        }
    }

    printf("%s %02d:%02d\n", day, hour, minute);

    return 0;
}
