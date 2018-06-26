#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct Mouse
{
    double weight;
    int rank;
};

int main()
{
    int np, ng;
    scanf("%d %d", &np, &ng);

    vector<Mouse> mice(np);
    queue<int> competitors;

    for (auto &m : mice) {
        scanf("%lf", &m.weight);
    }

    for (int i = 0; i < np; ++i) {
        int id;
        scanf("%d", &id);
        competitors.push(id);
    }

    while (competitors.size() != 1) {

        int size = competitors.size();
        int rank = (size + ng -1) / ng + 1;

        for (int i = 0; i < size;) {    
            double max = -1, winner;

            for (int j = 0; j < ng && i < size; ++j, ++i) {

                auto ci = competitors.front();
                competitors.pop();

                mice[ci].rank = rank;

                if (mice[ci].weight > max) {
                    max = mice[ci].weight;
                    winner = ci;
                }
            }

            competitors.push(winner);
        }
    }

    mice[competitors.front()].rank = 1;

    for (int i = 0, len = mice.size(); i < len; ++i) {
        if (i != 0) {
            printf(" ");
        }
        printf("%d", mice[i].rank);
    }

    printf("\n");

    return 0;
}
