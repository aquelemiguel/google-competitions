#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie();

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n, p;
        cin >> n >> p;

        int s[n];

        for (int j = 0; j < n; j++) {
            cin >> s[j]; 
        }

        sort(s, s + sizeof(s) / sizeof(s[0]), greater<int>());

        int min = INT_MAX;
        int pref[n];

        // Prefix sum
        pref[0] = s[0];

        for (int j = 1; j < n; j++) {
            pref[j] = pref[j-1] + s[j];
        }

        for (int j = 0; j < n-p+1; j++) {
            int diff = p * s[j] - (pref[j+p-1] - (j != 0 ? pref[j-1] : 0));

            if (diff < min) {
                min = diff;
            }
        }

        cout << "Case #" << i+1 << ": " << min << endl;
    }
}