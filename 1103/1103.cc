#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

bool SearchFactors(int target, int k, int rk, 
                   int factors_sum, int &pre_factors_sum,
                   vector<int> &largest_seq,
                   vector<int> &factors,
                   vector<int> &ppow)
{
    if (rk > k) {return false;}
    if (target < k - rk) {return true;}

    int upper_bound = rk > 1 ? factors[rk-2] : ppow.size()-1;

    for (int h = upper_bound, l = 1, limit = target-(k-rk); h > l;) {
        int upper_bound = (h + l) / 2;
        if (ppow[upper_bound] > limit) {
            h = upper_bound - 1;
        } else {
            break;
        }
    }

    int factors_left = k - rk + 1;

    if (pre_factors_sum > factors_sum &&
        pre_factors_sum - factors_sum >= upper_bound * factors_left) {
        return false;
    }

    for (int i = upper_bound; i >= 1; --i) {

        if (pre_factors_sum >= factors_sum + i * factors_left) {
            return true;
        }

        int new_target = target - ppow[i];

        if (rk < k) {
            factors[rk-1] = i;
            bool b = SearchFactors(new_target, k, rk+1, 
                                   factors_sum + i, pre_factors_sum, 
                                   largest_seq, factors, ppow);

            if (!b) {
                return false;
            }
        } else if (new_target == 0) {
            factors_sum += i;
            if (factors_sum > pre_factors_sum) {
                factors[rk-1] = i;
                pre_factors_sum = factors_sum;
                largest_seq = factors;
            }
            return true;
        }
    }

    return true;
}

int main()
{
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);

    vector<int> ppow;
    ppow.push_back(0);

    for (int i = 1, upper_bound = n-k+1; i <= upper_bound; ++i) {
        int ippow = pow(i, p);
        if (ippow > upper_bound) {break;}

        ppow.push_back(ippow);
    }

    vector<int> largest_seq(k), factors(k);
    int pre_factors_sum = 0;
    SearchFactors(n, k, 1, 0, pre_factors_sum, largest_seq, factors, ppow);

    if (pre_factors_sum == 0) {
        printf("Impossible\n");
        return 0;
    }

    printf("%d = ", n);
    for (int i = 0; i < k; ++i) {
        if (i != 0) {printf(" + ");}
        printf("%d^%d", largest_seq[i], int(p));
    }
    printf("\n");
    
    return 0;
}
