#include <cstdio>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct Student
{
    int id;
    int grades[4];

    Student() = default;
    Student(int i, int c, int m, int e): 
        id(i), grades{static_cast<int>(round(float(c+m+e)/3)), c, m, e} {};
};

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    char courses[] = {'A', 'C', 'M', 'E'};
    vector<Student> students;
    map<int, pair<int, int>> rank;

    for (int i = 0; i < N; ++i) {
        int id, c, m, e;
        scanf("%d %d %d %d", &id, &c, &m, &e);

        students.emplace_back(id, c, m, e);
    }

    for (int i = 0; i < 4; ++i) {
        sort(students.begin(), students.end(),
             [i](const Student &a, const Student &b) {
                 return a.grades[i] > b.grades[i];
             });


        for (int j = 0, r = 1, len = students.size(); j < len; ++j) {

            int id = students[j].id;

            if (j > 0 && students[j].grades[i] != students[j-1].grades[i]) {
                r = j + 1;
            }

            if (rank.find(id) == rank.cend() || r < rank[id].first) {
                rank[id] = {r, i};
            }
        }
    }

    for (int i = 0; i < M; ++i) {
        int id;
        scanf("%d", &id);

        if (rank.find(id) == rank.cend()) {
            printf("N/A\n");
        } else {
            printf("%d %c\n", rank[id].first, courses[rank[id].second]);
        }
    }
    
    return 0;
}
