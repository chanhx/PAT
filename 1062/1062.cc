#include <cstdio>
#include <vector>
#include <algorithm>

struct Person {
    int id;
    int virtue;
    int talent;
    int sum;

    Person() = default;
    Person(int i, int v, int t): id(i), virtue(v), talent(t), sum(v+t) {};
};


int main()
{
    int n, L, H;
    scanf("%d %d %d", &n, &L, &H);

    std::vector<Person> sages, noblemen, fool_men, rest;
    std::vector<Person> vectors[] = {sages, noblemen, fool_men, rest};

    for (int i = 0; i < n; ++i) {
        int id, virtue, talent;
        scanf("%d %d %d", &id, &virtue, &talent);

        if (virtue < L || talent < L) {
            continue;
        }

        int j;
        if (virtue >= H && talent >= H) {
            j = 0;
        } else if (virtue >= H && talent < H) {
            j = 1;
        } else if (virtue < H && talent < H && virtue >= talent) {
            j = 2;
        } else {
            j = 3;
        }
        vectors[j].emplace_back(id, virtue, talent);
    }

    int n2 = 0;
    for (auto &v : vectors) {
        n2 += v.size();
    }
    printf("%d\n", n2);

    for (auto &v : vectors) {
        if (v.size() <= 0) {
            continue;
        }

        std::sort(v.begin(), v.end(),
                  [](const Person &a, const Person &b) {
                      if (a.sum != b.sum) {
                          return a.sum > b.sum;
                      } else if (a.virtue != b.virtue) {
                          return a.virtue > b.virtue;
                      } else {
                          return a.id < b.id;
                      }
                  });

        for (const auto &p : v) {
            printf("%d %d %d\n", p.id, p.virtue, p.talent);
        }
    }

    return 0;
}
