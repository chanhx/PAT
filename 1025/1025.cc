#include <cstdio>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>

using namespace std;

struct Student
{
    char id[15];
    int score;
    int location;
};

int main()
{
    int n;
    scanf("%d", &n);

    vector<Student> students;

    // {location: (previous_score, rank, count_of_people)}
    unordered_map<int, tuple<int, int, int>> pre_scores; 

    for (int i = 0; i < n; ++i) {
        int k;
        scanf("%d", &k);

        for (int j = 0; j < k; ++j) {
            Student s;
            scanf("%s %d", s.id, &s.score);
            s.location = i + 1;

            students.push_back(s);
        }
    }

    sort(students.begin(), students.end(),
         [](const Student &a, const Student &b) {
             if (a.score != b.score) {
                 return a.score > b.score;
             } else {
                 return strcmp(a.id, b.id) < 0;
             }
         });

    printf("%lu\n", students.size());

    for (int i = 0, len = students.size(), fr = 1; i < len; ++i) {
        
        auto s = students[i];

        if (i > 0 && s.score != students[i-1].score) {
            fr = i + 1;
        }

        int lr = 1, j = 1;
        if (pre_scores.find(s.location) != pre_scores.cend()) {
            auto t = pre_scores[s.location];
            lr = get<1>(t);
            j = get<2>(t) + 1;

            if (s.score != get<0>(t)) {
                lr = j;
            }
        }
        pre_scores[s.location] = make_tuple(s.score, lr, j);

        printf("%s %d %d %d\n", s.id, fr, s.location, lr);
    }

    return 0;
}
