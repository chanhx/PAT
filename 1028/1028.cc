#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct Record
{
    int id;
    char name[10];
    int grade;
};

int main()
{
    int n, c;
    scanf("%d %d", &n, &c);

    vector<Record> records(n);

    for (auto &r : records) {
        scanf("%d %s %d", &r.id, r.name, &r.grade);
    }
    
    sort(records.begin(), records.end(),
         [c](const Record &a, const Record &b) {
             auto b_id = a.id < b.id;;
             if (c == 2) {
                 auto b_name = strcmp(a.name, b.name);
                 if (b_name != 0) {
                     return b_name < 0;
                 }
             } else if (c == 3) {
                 if (a.grade != b.grade) {
                     return a.grade < b.grade;
                 }
             }

             return b_id;
         });

    for (const auto &r : records) {
        printf("%06d %s %d\n", r.id, r.name, r.grade);
    }

    return 0;
}
