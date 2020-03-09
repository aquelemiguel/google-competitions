#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie();

    int tc;
    cin >> tc;

    for (int t = 1; t <= tc; t++) {
        int n;
        string s;
        cin >> n >> s;

        int pref[n];
        int p = ceil(n/2.0);

        for (int i = 0; i < n; i++) {
            pref[i] = s[i] - '0';
        }

        for (int i = 1; i < n; i++) {
            pref[i] += pref[i-1];
        }

        int max_sum = pref[p-1]; 

        for (int i = 1; i <= n - p; i++) {
            int new_sum = pref[i+p-1] - pref[i-1];
            if (new_sum > max_sum) max_sum = new_sum;
        }

        cout << "Case #" << t << ": " << max_sum << endl;
    }
}