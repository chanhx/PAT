#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Mooncake
{
    double amount;
    double total_price;
    double price;
};

int main()
{
    int n;
    double demand, profit = 0;
    scanf("%d %lf", &n, &demand);

    vector<Mooncake> mooncakes(n);

    for (auto &m : mooncakes) {
        scanf("%lf", &m.amount);
    }

    for (auto &m : mooncakes) {
        scanf("%lf", &m.total_price);
        m.price = m.total_price / m.amount;
    }

    sort(mooncakes.begin(), mooncakes.end(),
         [](const Mooncake &a, const Mooncake &b) {
             return a.price > b.price;
         });
    
    for (auto const &m : mooncakes) {
        if (m.amount <= demand) {
            demand -= m.amount;
            profit += m.total_price;
        } else {            
            profit += m.price * demand;
            demand = 0;
        }
    }

    printf("%.2f\n", profit);

    return 0;
}
