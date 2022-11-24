#include <bits/stdc++.h>

int main() {
    long long n;
    std::cin >> n;
    std::vector<std::vector<long long>> dp(n + 1, std::vector<long long> (n + 1));
    dp[2][0] = 1;
    dp[2][1] = 1;
    dp[2][2] = 1;
    for (long long len = 3; len <= n; ++len) {
        for (long long j = 1; j <= n; ++j) {
            dp[len][j] = dp[len - 1][j - 1];
        }
        for (long long j = 2; j <= n; ++j) {
            dp[len][0] += dp[len - 1][j];
        }
    }
    long long ans = 0;
    for (long long i = 0; i <= n; ++i) {
        ans += dp[n][i];
    }
    std::cout << ans << '\n';
}