#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

struct Point
{
    int x, y, z;

    Point() = default;
    Point(int i, int j, int k): x(i), y(j), z(k) {};
};

int main()
{
    int m, n, l, t;
    scanf("%d %d %d %d", &m, &n, &l, &t);

    int total_volume = 0;
    vector<vector<vector<int>>> slices(m, vector<vector<int>>(n, vector<int>(l)));
    queue<Point> pixels;

    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                scanf("%d", &slices[j][k][i]);
            }
        }
    }
    
    for (int i = 0, core_volume = 0; i < l; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                
                if (slices[j][k][i] == 0) {
                    continue;
                }

                pixels.emplace(j, k, i);

                while (pixels.size() > 0) {
                    
                    auto point = pixels.front();
                    int x = point.x, y = point.y, z = point.z;
                    pixels.pop();

                    if (slices[x][y][z] != 1) {
                        continue;
                    }

                    ++core_volume;
                    slices[x][y][z] = 0;

                    if (z > 0 && slices[x][y][z-1] == 1) {
                        pixels.emplace(x, y, z-1);
                    }
                    if (z < l-1 && slices[x][y][z+1] == 1) {
                        pixels.emplace(x, y, z+1);
                    }

                    if (x > 0 && slices[x-1][y][z] == 1) {
                        pixels.emplace(x-1, y, z);
                    }
                    if (x < m-1 && slices[x+1][y][z] == 1) {
                        pixels.emplace(x+1, y, z);
                    }

                    if (y > 0 && slices[x][y-1][z] == 1) {
                        pixels.emplace(x, y-1, z);
                    }
                    if (y < n-1 && slices[x][y+1][z] == 1) {
                        pixels.emplace(x, y+1, z);
                    }
                }

                if (core_volume >= t) {
                    total_volume += core_volume;
                }
                core_volume = 0;
            }
        }
    }

    printf("%d\n", total_volume);

    return 0;
}
