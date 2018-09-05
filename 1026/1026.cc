#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Pair
{
    int arriving_time;
    int playing_time;
    int serving_time;
    bool vip;
};

struct Table
{
    int serving_time;
    int pairs_count;
    bool for_vip;
};

inline int ConvertTime(int h, int m, int s)
{
    return h * 3600 + m * 60 + s;
}

inline void SortPairs(vector<Pair> &pairs)
{
    sort(pairs.begin(), pairs.end(),
         [](const Pair &a, const Pair &b) {
             return a.arriving_time < b.arriving_time;
         });
}

inline void PrintTime(int time)
{
    printf("%02d:%02d:%02d ", time / 3600, time % 3600 / 60, time % 60);
}

inline void PrintTimeInfo(const Pair &p)
{
    PrintTime(p.arriving_time); 
    PrintTime(p.serving_time);
    printf("%.0f\n", round((p.serving_time - p.arriving_time) / 60.0));
}

int main()
{
    int n;
    scanf("%d\n", &n);

    int begin_time = ConvertTime(8, 0, 0);
    int end_time = ConvertTime(21, 0, 0);

    vector<Pair> ordinary_pairs, vip_pairs;

    for (int i = 0; i < n; ++i) {
        int h, m, s, playing_time, vip;
        scanf("%d:%d:%d %d %d", &h, &m, &s, &playing_time, &vip);

        auto arriving_time = ConvertTime(h, m, s);

        if (arriving_time >= end_time) {
            continue;
        }

        if (playing_time > 120) {
            playing_time = 120;
        }

        Pair p = {arriving_time, playing_time * 60, 0, vip == 1};
        (p.vip ? vip_pairs : ordinary_pairs).push_back(p);
    }

    SortPairs(ordinary_pairs);
    SortPairs(vip_pairs);

    int k, m;
    scanf("%d %d", &k, &m);

    vector<Table> tables(k+1, {begin_time, 0, false});

    for (int i = 0, t; i < m; ++i) {
        scanf("%d", &t);
        tables[t].for_vip = true;
    }

    auto oit = ordinary_pairs.begin(),
         oend = ordinary_pairs.end(),
         vit = vip_pairs.begin(),
         vend = vip_pairs.end();

    while (oit != oend || vit != vend) {
        int ti, ti_vip;
        for (int i = 1, earliest = INF, earliest_vip = INF; i <= k; ++i) {
            auto &t = tables[i];
            if (t.serving_time < earliest) {
                earliest = t.serving_time;
                ti = i;
            }
            if (t.for_vip && t.serving_time < earliest_vip) {
                earliest_vip = t.serving_time;
                ti_vip = i;
            }
        }

        if (tables[ti].serving_time >= end_time) {break;}

        decltype(vit) it;

        if (tables[ti].for_vip &&
            vit != vend &&
            (*vit).arriving_time <= tables[ti].serving_time)
        {
            it = vit;
            ++vit;
        } else if (oit != oend && vit != vend) {
            if ((*vit).arriving_time < (*oit).arriving_time) {
                it = vit;
                ++vit;
            } else {
                it = oit;
                ++oit;
            }
        } else if (oit != oend) {
            it = oit;
            ++oit;
        } else {
            it = vit;
            ++vit;
        }

        if (ti != ti_vip &&
            ti_vip != INF &&
            (*it).vip &&
            tables[ti_vip].serving_time <= (*it).arriving_time)
        {
            ti = ti_vip;
        }

        auto &t = tables[ti];

        (*it).serving_time = max(t.serving_time, (*it).arriving_time);
        t.serving_time = (*it).serving_time + (*it).playing_time;
        ++t.pairs_count;

        PrintTimeInfo(*it);
    }

    for (int i = 1; i <= k; ++i) {
        printf("%d%c", tables[i].pairs_count, i == k ? '\n' : ' ');
    }

    return 0;
}