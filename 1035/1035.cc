#include <cstdio>
#include <cstring>

using namespace std;

char modifieds[1000][22];

inline bool ModifyPassword(char *password)
{
    bool modified = false;

    for (int i = 0, len = strlen(password); i < len; ++i) {
        switch (password[i]) {
            case '1': 
                password[i] = '@'; 
                modified = true;
                break;
            case '0': 
                password[i] = '%';
                modified = true;
                break;
            case 'l': 
                password[i] = 'L';
                modified = true;
                break;
            case 'O': 
                password[i] = 'o';
                modified = true;
                break;
            default: break;
        }
    }

    return modified;
}

int main()
{
    int n, num_modified = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        char name[11], password[11];
        scanf("%s %s", name, password);

        if (ModifyPassword(password)) {
            sprintf(modifieds[num_modified], "%s %s", name, password);
            ++num_modified;
        }
    }

    if (!num_modified) {
        const char *be = n > 1 ? "are" : "is";
        const char *noun = n > 1 ? "accounts" : "account";

        printf("There %s %d %s and no account is modified\n", be, n, noun);
    } else {
        printf("%d\n", num_modified);
        for (int i = 0; i < num_modified; ++i) {
            printf("%s\n", modifieds[i]);
        }
    }

    return 0;
}
