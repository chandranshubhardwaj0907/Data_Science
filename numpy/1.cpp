#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

void solve() {
    int n;
    long long m;
    std::cin >> n >> m;

    std::vector<long long> schedule;
    schedule.push_back(0);
    for (int i = 0; i < n; ++i) {
        long long val;
        std::cin >> val;
        schedule.push_back(val);
    }
    schedule.push_back(m);

    int schedule_size = schedule.size();
    std::vector<long long> suffix_on(schedule_size + 1, 0);
    std::vector<long long> suffix_off(schedule_size + 1, 0);

    for (int i = schedule_size - 2; i >= 0; --i) {
        suffix_on[i] = suffix_on[i + 1];
        suffix_off[i] = suffix_off[i + 1];
        if (i % 2 == 0) {
            suffix_on[i] += schedule[i + 1] - schedule[i];
        } else {
            suffix_off[i] += schedule[i + 1] - schedule[i];
        }
    }

    long long max_on_time = suffix_on[0];
    long long prefix_on_sum = 0;

    for (int i = 0; i < schedule_size - 1; ++i) {
        if (schedule[i + 1] - schedule[i] > 1) {
            long long gain_from_interval = schedule[i + 1] - schedule[i] - 1;
            long long rest_on_time_after_flip = suffix_off[i + 1];
            long long current_total_on = prefix_on_sum + gain_from_interval + rest_on_time_after_flip;
            if (current_total_on > max_on_time) {
                max_on_time = current_total_on;
            }
        }

        if (i % 2 == 0) {
            prefix_on_sum += schedule[i + 1] - schedule[i];
        }
    }

    std::cout << max_on_time << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    solve();
    return 0;
}
